/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:28:03 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/09 21:41:29 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_action(t_philo *philo)
{
	//왜 think 안하는지 확인해보기
	while (philo->is_live == LIVE)
	{
		// printf("-----[%d] left : %d, right : %d\n", philo->num, philo->forks[LEFT]->state, philo->forks[RIGHT]->state);
		if (philo->forks[LEFT]->state == LOCK || philo->forks[RIGHT]->state == LOCK)
		{
			if (do_think(philo) == 0)
				return (0);
		}
		if (do_eat(philo) == 0)
			return (0);
		if (do_sleep(philo) == 0)
			return (0);
	}
	return (0);
}

int	do_eat(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	philo->forks[LEFT]->state = LOCK;
	philo->forks[RIGHT]->state = LOCK;
	pthread_mutex_lock(&philo->forks[LEFT]->mutex);
	pthread_mutex_lock(&philo->forks[RIGHT]->mutex);
	printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(philo, START), philo->num);
	printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(philo, START), philo->num);
	printf("%s%ld %d is eating\n", C_GREN, get_time_diff(philo, START), philo->num);

	gettimeofday(&(philo->recent), NULL);
	check_usleep(philo->argv[TIME_EAT]);
	// usleep(philo->argv[TIME_EAT]); //usleep 정확도 체크 필요
	
	pthread_mutex_unlock(&philo->forks[LEFT]->mutex);
	pthread_mutex_unlock(&philo->forks[RIGHT]->mutex);
	philo->forks[LEFT]->state = UNLOCK;
	philo->forks[RIGHT]->state = UNLOCK;
	return (1);
}

int	do_sleep(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	printf("%s%ld %d is sleeping\n", C_YLLW, get_time_diff(philo, START), philo->num);
	check_usleep(philo->argv[TIME_SLEEP]);
	// usleep(philo->argv[TIME_SLEEP]); //usleep 정확도 체크 필요
	return (1);
}

int	do_think(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	printf("%s%ld %d is thinking\n", C_BLUE, get_time_diff(philo, START), philo->num);
	while (!(philo->forks[LEFT]->state == UNLOCK && philo->forks[RIGHT]->state == UNLOCK))
	{
		if (am_i_die(philo) == DIE)
			return (0);
	}
	return (1);
}
