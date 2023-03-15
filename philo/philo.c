/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/15 18:09:16 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_table *table)
{
	int	i;
	int	j;

	j = 1;
	while (1)
	{
		i = 1;
		while (i <= table->argv[NUM_PHILO])
		{
			if (are_you_die(&(table->philos[i]), table->argv) == DIE || check_eat_enough(&(table->philos[i])) == TRUE)
			{
				i = 1;
				while (i <= table->argv[NUM_PHILO])
				{
					pthread_join(table->threads[i], NULL);
					i++;
				}
				i = 1;
				while (i <= table->argv[NUM_PHILO])
				{
					pthread_mutex_destroy(&(table->forks[i].mutex));
					i++;
				}
				pthread_mutex_destroy(&(table->live.mutex));
				pthread_mutex_destroy(&(table->print));
				return (0);
			}
			usleep(300); // 필요한가?
			i++;
		}
	}
	return (0);
}

int	check_eat_enough(t_philo *philo)
{
	if (check_eat_count(philo) == TRUE)
	{
		pthread_mutex_lock(&(philo->live->mutex));
		philo->live->is_live = DIE;
		pthread_mutex_unlock(&(philo->live->mutex));
		return (TRUE);
	}
	else
		return (FALSE);
}

int	check_eat_count(t_philo *philo)
{
	int	is_enough;

	is_enough = FALSE;
	if (philo->argv[MUST_EAT] == 0)
		return (FALSE);
	pthread_mutex_lock(&(philo->eat_info.mutex));
	if (philo->eat_info.count >= philo->argv[MUST_EAT])
		is_enough = TRUE;
	pthread_mutex_unlock(&(philo->eat_info.mutex));
	return (is_enough);
}


int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == 0)
		return (0); //유효하지 않은 인자 에러
	if (init_fork(&table) == -1)
		return (0); //malloc 에러
	init_print_live(&table);
	if (init_philo(&table) == -1)
		return (0); //malloc 에러
	gettimeofday(&(table.start_time), NULL);
	if (init_thread(&table) == -1)
		return (0); //malloc 에러
	check_die(&table);
	return (0);
}
