/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:39:45 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/13 13:10:16 by hahlee           ###   ########.fr       */
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
			return (0);
		tmp[j] = ft_atoi(src[i]);
		if (tmp[j] == 0 || tmp[j] > INT_MAX)
			return (0);
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
	int		i;

	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->argv[NUM_PHILO]);
	if (table->forks == NULL)
		return (-1); //table ㅎㅐ제 해야함
	i = 0;
	while (i < table->argv[NUM_PHILO])
	{
		if (pthread_mutex_init(&(table->forks[i].mutex), NULL) != 0)
			return (safe_free((void **)&table->forks, -1));
		table->forks[i].state = UNLOCK;
		i++;
	}
	return (0);
}

int	init_philo(t_table *table)
{
	t_philo	*philo;
	int		num_philo;
	int		i;

	num_philo = table->argv[NUM_PHILO];
	table->philos = (t_philo *)malloc(sizeof(t_philo) * num_philo);
	if (table->philos == NULL)
		return (-1); //forks 를 여기서 free?
	i = 0;
	while (i < num_philo)
	{
		philo = (table->philos + i);
		philo->num = i;
		philo->is_live = LIVE;
		// philo->forks[LEFT] = &(table->forks[table->argv[NUM_PHILO] - i - 1]);
		// philo->forks[RIGHT] = &(table)->forks[i];
		philo->forks[LEFT] = &(table)->forks[i];
		if (i == num_philo - 1)
			philo->forks[RIGHT] = &(table)->forks[0];
		else
			philo->forks[RIGHT] = &(table)->forks[i + 1];
		philo->argv = table->argv;
		philo->start = &(table->start);
		philo->recent = table->start;
		i++;
	}
	return (0);
}

int	init_thread(t_table *table)
{
	int	i;

	table->threads = (pthread_t *)malloc(sizeof(pthread_t) * table->argv[NUM_PHILO]);
	if (table->threads == NULL)
		return (-1); //fork, philo ㅇㅕ기서 free?
	i = 0;
	while (i < table->argv[NUM_PHILO])
	{
		if (pthread_create(&(table->threads[i]), NULL, (void *)do_action, &(table->philos[i])) != 0)
			return (-1); // 기존 스레드 종료? 리턴값 고민해보기
		i++;
	}
	return (0);
}
