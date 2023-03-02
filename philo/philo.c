/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/02 13:24:06 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h> //
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

int	init_fork(t_table **table)
{
	int		i;

	(*table)->forks = (t_fork *)malloc(sizeof(t_fork) * (*table)->argv[NUM_PHILO]);
	if ((*table)->forks == NULL)
		return (-1); //table ㅎㅐ제 해야함
	i = 0;
	while (i < (*table)->argv[NUM_PHILO])
	{
		if (pthread_mutex_init(&((*table)->forks[i].mutex), NULL) != 0)
			return (safe_free((void **)&(*table)->forks, -1));
		(*table)->forks[i].state = UNLOCK;
		i++;
	}
	return (0);
}

int	init_philo(t_table **table)
{
	int	i;

	(*table)->philos = (t_philo *)malloc(sizeof(t_philo) * (*table)->argv[NUM_PHILO]);
	if ((*table)->philos == NULL)
		return (-1); //forks 를 여기서 free?
	i = 0;
	while (i < (*table)->argv[NUM_PHILO])
	{
		(*table)->philos[i].num = i;
		(*table)->philos[i].is_alive = LIVE;
		(*table)->philos[i].forks[LEFT] = (*table)->forks[(*table)->argv[NUM_PHILO] - i - 1];
		(*table)->philos[i].forks[RIGHT] = (*table)->forks[(*table)->argv[i]];
		(*table)->philos[i].argv = (*table)->argv;
		(*table)->philos[i].start = &((*table)->start);
		i++;
	}
	return (0);
}

int	init_thread(t_table **table)
{
	int	i;

	(*table)->threads = (pthread_t *)malloc(sizeof(pthread_t) * (*table)->argv[NUM_PHILO]);
	if ((*table)->threads == NULL)
		return (-1); //fork, philo ㅇㅕ기서 free?
	i = 0;
	while (i < (*table)->argv[NUM_PHILO])
	{
		if (pthread_create(&((*table)->threads[i]), NULL, (void *)test, &((*table)->philos[i])) != 0)
			return (-1); // 기존 스레드 종료? 리턴값 고민해보기
		i++;
	}
	return (0);
}

int	test(t_philo *philo)
{
	struct timeval end;

	printf("hi! im %d\n", philo->num);
	gettimeofday(&end, NULL);
	printf("%ld\n", (end.tv_sec - philo->start->tv_sec) + ((end.tv_usec - philo->start->tv_usec) / 1000000));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (0);
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (0);
	if (init_argv(argc, argv, &(table->argv)) == 0)
		return (0); //유효하지 않은 인자 에러
	if (init_fork(&table) == -1)
		return (0); //malloc or 뮤텍스 생성실패
	if (init_philo(&table) == -1)
		return (0); //malloc 에러
	if (gettimeofday(&(table->start), NULL) == -1)
		return (0);
	if (init_thread(&table) == -1)
		return (0); //malloc 에러 or 스레드 생성실패
}
