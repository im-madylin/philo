/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:20:09 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/15 17:11:43 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
