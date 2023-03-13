/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:28:03 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/13 19:21:04 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_action(t_philo *philo)
{
	if (philo->num % 2 == 0)
		msleep(100);
	while (*(philo->is_live) == LIVE)
	{
		// if (philo->forks[LEFT]->state == LOCK || philo->forks[RIGHT]->state == LOCK)
		// {
		// 	if (do_think(philo) == 0)
		// 		return (0);
		// }
		if (do_think(philo) == 0)
			return (0);
		if (do_eat(philo) == 0)
			return (0);
		if (do_sleep(philo) == 0)
			return (0);
		usleep(300);
	}
	return (0);
}

int	do_eat(t_philo *philo)
{
	pick_up_fork(philo);
	if (am_i_die(philo) == DIE)
		return (0);
	printf("%s%ld %d is eating\n", C_GREN, get_time_diff(*(philo->start)), philo->num);
	gettimeofday(&(philo->recent), NULL);
	msleep(philo->argv[TIME_EAT]);
	put_down_fork(philo);
	return (1);
}

void	pick_up_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		if (am_i_die(philo) == DIE)
			return ;
		philo->forks[LEFT]->state = LOCK;
		pthread_mutex_lock(&philo->forks[LEFT]->mutex);
		printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(*(philo->start)), philo->num);
		if (am_i_die(philo) == DIE)
			return ;
		philo->forks[RIGHT]->state = LOCK;
		pthread_mutex_lock(&philo->forks[RIGHT]->mutex);
		printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(*(philo->start)), philo->num);
	}
	else
	{
		if (am_i_die(philo) == DIE)
			return ;
		philo->forks[RIGHT]->state = LOCK;
		pthread_mutex_lock(&philo->forks[RIGHT]->mutex);
		printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(*(philo->start)), philo->num);
		if (am_i_die(philo) == DIE)
			return ;
		philo->forks[LEFT]->state = LOCK;
		pthread_mutex_lock(&philo->forks[LEFT]->mutex);
		printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(*(philo->start)), philo->num);
	}
}

void	put_down_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		pthread_mutex_unlock(&philo->forks[LEFT]->mutex);
		philo->forks[LEFT]->state = UNLOCK;
		pthread_mutex_unlock(&philo->forks[RIGHT]->mutex);
		philo->forks[RIGHT]->state = UNLOCK;
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[RIGHT]->mutex);
		philo->forks[RIGHT]->state = UNLOCK;
		pthread_mutex_unlock(&philo->forks[LEFT]->mutex);
		philo->forks[LEFT]->state = UNLOCK;
	}
}

int	do_sleep(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	printf("%s%ld %d is sleeping\n", C_YLLW, get_time_diff(*(philo->start)), philo->num);
	msleep(philo->argv[TIME_SLEEP]);
	return (1);
}

int	do_think(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	printf("%s%ld %d is thinking\n", C_BLUE, get_time_diff(*(philo->start)), philo->num);
	msleep(philo->argv[TIME_DIE] - (philo->argv[TIME_EAT] + philo->argv[TIME_SLEEP] + 50));
	// while (!(philo->forks[LEFT]->state == UNLOCK && philo->forks[RIGHT]->state == UNLOCK))
	// {
	// 	if (am_i_die(philo) == DIE)
	// 		return (0);
	// 	usleep(300);
	// }
	return (1);
}
