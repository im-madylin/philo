/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:20:09 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/16 15:00:03 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		lock_the_fork(philo, LEFT);
		if (philo->argv[NUM_PHILO] != 1)
			lock_the_fork(philo, RIGHT);
		else
			msleep(philo->argv[TIME_EAT] + philo->argv[TIME_SLEEP] + 50);
	}
	else
	{
		lock_the_fork(philo, RIGHT);
		lock_the_fork(philo, LEFT);
	}
}

void	lock_the_fork(t_philo *philo, int flag)
{
	t_fork	*forks;

	forks = philo->forks[LEFT];
	if (flag == RIGHT)
		forks = philo->forks[RIGHT];
	while (1)
	{
		if (am_i_die(philo) == DIE)
			return ;
		pthread_mutex_lock(&forks->mutex);
		if (forks->state == UNLOCK)
		{
			forks->state = LOCK;
			print_message(philo, FORK);
			pthread_mutex_unlock(&forks->mutex);
			return ;
		}
		else
		{
			pthread_mutex_unlock(&forks->mutex);
		}
	}
}

void	put_down_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		unlock_the_fork(philo, LEFT);
		unlock_the_fork(philo, RIGHT);
	}
	else
	{
		unlock_the_fork(philo, RIGHT);
		unlock_the_fork(philo, LEFT);
	}
}

void	unlock_the_fork(t_philo *philo, int flag)
{
	t_fork	*forks;

	forks = philo->forks[LEFT];
	if (flag == RIGHT)
		forks = philo->forks[RIGHT];
	if (am_i_die(philo) == DIE)
		return ;
	pthread_mutex_lock(&forks->mutex);
	if (forks->state == LOCK)
	{
		forks->state = UNLOCK;
		pthread_mutex_unlock(&forks->mutex);
		return ;
	}
	pthread_mutex_unlock(&forks->mutex);
	// else 인 경우가 있나?
}
