/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:11:49 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/22 19:12:21 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_table *table)
{
	t_philo	*philo;
	int		num_philo;
	int		i;

	num_philo = table->argv[NUM_PHILO];
	table->philos = (t_philo *)malloc(sizeof(t_philo) * (num_philo + 1));
	if (table->philos == NULL)
		return (FALSE);
	i = 0;
	while (++i <= num_philo)
	{
		philo = table->philos + i;
		philo->id = i;
		philo->live = &(table->live);
		philo->forks[LEFT] = &(table)->forks[i];
		philo->forks[RIGHT] = &(table)->forks[1];
		if (i != num_philo)
			philo->forks[RIGHT] = &(table)->forks[i + 1];
		philo->argv = table->argv;
		philo->start_time = &(table->start_time);
		if (init_eat_info(table, i) == FALSE)
			return (safe_free((void **)&(table->philos)));
		philo->print = &(table->print);
	}
	return (TRUE);
}

int	init_eat_info(t_table *table, int i)
{
	t_philo	*philo;

	philo = table->philos + i;
	philo->eat_info.mutex = (t_mutex *)malloc(sizeof(t_mutex));
	if (philo->eat_info.mutex == NULL)
	{
		i -= 1;
		while (i > 0)
		{
			safe_free((void **)&(philo->eat_info.mutex));
			i--;
		}
		return (FALSE);
	}
	pthread_mutex_init(philo->eat_info.mutex, NULL);
	philo->eat_info.count = 0;
	philo->eat_info.is_enough = FALSE;
	return (TRUE);
}

int	init_thread(t_table *table)
{
	int	num_philo;
	int	i;

	num_philo = table->argv[NUM_PHILO] + 1;
	table->threads = (pthread_t *)malloc(sizeof(pthread_t) * num_philo);
	if (table->threads == NULL)
		return (FALSE);
	i = 1;
	while (i <= table->argv[NUM_PHILO])
	{
		pthread_create(&(table->threads[i]), NULL, \
		(void *)do_action, &(table->philos[i]));
		i++;
	}
	return (TRUE);
}
