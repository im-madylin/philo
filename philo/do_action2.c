/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:20:09 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/14 20:12:06 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_left_fork(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return ;
	philo->forks[LEFT]->state = LOCK;
	pthread_mutex_lock(&philo->forks[LEFT]->mutex);
	print_message(philo, FORK);
}

void	pick_up_right_fork(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return ;
	if (philo->forks[RIGHT]->state != LOCK)
	{
		philo->forks[RIGHT]->state = LOCK;
		pthread_mutex_lock(&philo->forks[RIGHT]->mutex);
		print_message(philo, FORK);
	}
}

void	put_down_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		pick_down_left_fork(philo);
		pick_down_right_fork(philo);
	}
	else
	{
		pick_down_right_fork(philo);
		pick_down_left_fork(philo);
	}
}

void	pick_down_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[LEFT]->mutex);
	philo->forks[LEFT]->state = UNLOCK;
}

void	pick_down_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->forks[RIGHT]->mutex);
	philo->forks[RIGHT]->state = UNLOCK;
}
