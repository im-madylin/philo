/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:39:45 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/22 19:12:37 by hahlee           ###   ########.fr       */
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

int	init_struct(int argc, char *argv[], t_table *table)
{
	if (init_argv(argc, argv, &(table->argv)) == FALSE)
		return (FALSE);
	if (init_fork(table) == FALSE)
		return (FALSE);
	init_print_live(table);
	if (init_philo(table) == FALSE)
		return (safe_free((void **)&(table->forks)));
	gettimeofday(&(table->start_time), NULL);
	if (init_thread(table) == FALSE)
		return (safe_free((void **)&(table->forks)), \
		free_eat_info(table), safe_free((void **)&(table->philos)));
	return (TRUE);
}
