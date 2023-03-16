/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:39:45 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/16 18:55:20 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_argv(int argc, char *src[], int argv[][5])
{
	int	tmp[5];
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (src[i][0] == '-' || ft_strlen(src[i]) > 10)
			return (FALSE);
		tmp[j] = ft_atoi(src[i]);
		if (tmp[j] == 0 || tmp[j] > INT_MAX)
			return (FALSE);
		i++;
		j++;
	}
	(*argv)[NUM_PHILO] = tmp[0];
	(*argv)[TIME_DIE] = tmp[1];
	(*argv)[TIME_EAT] = tmp[2];
	(*argv)[TIME_SLEEP] = tmp[3];
	(*argv)[MUST_EAT] = 0;
	if (argc == 6)
		(*argv)[MUST_EAT] = tmp[4];
	return (1);
}

int	init_fork(t_table *table)
{
	int		num_philo;
	int		i;

	num_philo = table->argv[NUM_PHILO] + 1;
	table->forks = (t_fork *)malloc(sizeof(t_fork) * num_philo);
	if (table->forks == NULL)
		return (FALSE);
	i = 1;
	while (i <= table->argv[NUM_PHILO])
	{
		pthread_mutex_init(&(table->forks[i].mutex), NULL);
		table->forks[i].state = UNLOCK;
		i++;
	}
	return (TRUE);
}

void	init_print_live(t_table *table)
{
	pthread_mutex_init(&(table->print), NULL);
	pthread_mutex_init(&(table->live.mutex), NULL);
	table->live.is_live = LIVE;
}

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
		philo = (table->philos + i);
		philo->num = i;
		philo->live = &(table->live);
		philo->forks[LEFT] = &(table)->forks[i];
		philo->forks[RIGHT] = &(table)->forks[1];
		if (i != num_philo)
			philo->forks[RIGHT] = &(table)->forks[i + 1];
		philo->argv = table->argv;
		philo->start_time = &(table->start_time);
		pthread_mutex_init(&(philo->eat_info.mutex), NULL);
		philo->eat_info.count = 0;
		philo->print = &(table->print);
	}
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
