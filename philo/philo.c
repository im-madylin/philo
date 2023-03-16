/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/16 15:35:25 by hahlee           ###   ########.fr       */
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
			if (are_you_die(&(table->philos[i]), table->argv) == DIE \
			|| check_eat_enough(table) == TRUE)
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
					pthread_mutex_destroy(&(table->philos[i].eat_info.mutex));
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

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == FALSE)
		return (0);
	if (init_fork(&table) == FALSE)
		return (0);
	init_print_live(&table);
	if (init_philo(&table) == FALSE)
		return (safe_free((void**)&(table.forks)));
	gettimeofday(&(table.start_time), NULL);
	if (init_thread(&table) == FALSE)
		return (safe_free((void**)&(table.forks)), safe_free((void**)&(table.philos)));
	check_die(&table);
	safe_free((void**)&(table.forks));
	safe_free((void**)&(table.philos));
	safe_free((void**)&(table.threads));
	return (0);
}
