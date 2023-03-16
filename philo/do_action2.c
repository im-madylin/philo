/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:20:09 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/16 18:49:33 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		lock_the_fork(philo, LEFT);
		if (philo->argv[NUM_PHILO] == 1)
			spend_time_when_alone(philo);
		else
			lock_the_fork(philo, RIGHT);
	}
	else
	{
		lock_the_fork(philo, RIGHT);
		lock_the_fork(philo, LEFT);
	}
}

void	spend_time_when_alone(t_philo *philo)
{
	int	spend_time;
	int	spare_time;

	spend_time = get_time_diff(*(philo->start_time));
	spare_time = philo->argv[TIME_DIE] - spend_time + 10;
	msleep(spare_time);
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
}
