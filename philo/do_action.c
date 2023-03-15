/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:28:03 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/15 17:59:47 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_action(t_philo *philo)
{
	if (philo->num % 2 == 0)
		msleep(100);
	while (am_i_die(philo) == LIVE)
	{
		if (do_think(philo) == 0)
			return (0);
		if (do_eat(philo) == 0)
			return (0);
		if (do_sleep(philo) == 0)
			return (0);
		usleep(300); //필요할까?
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	print_message(philo, THINK);
	msleep(philo->argv[TIME_DIE] - (philo->argv[TIME_EAT] + philo->argv[TIME_SLEEP] + 50));
	return (1);
}

int	do_eat(t_philo *philo)
{
	pick_up_fork(philo);
	if (am_i_die(philo) == DIE)
	{
		// if (philo->forks[LEFT]->state == LOCK)
		// 	pthread_mutex_unlock(&(philo->forks[LEFT]->mutex));
		// if (philo->forks[RIGHT]->state == LOCK)
		// 	pthread_mutex_unlock(&(philo->forks[RIGHT]->mutex));
		return (0);
	}
	print_message(philo, EAT);
	// philo->eat_info->count++;
	plus_eat_count(philo);
	gettimeofday(&(philo->recent_time), NULL);
	msleep(philo->argv[TIME_EAT]);
	put_down_fork(philo);
	return (1);
}

void	plus_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat_info.mutex));
	philo->eat_info.count++;
	pthread_mutex_unlock(&(philo->eat_info.mutex));
}

void	pick_up_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		lock_the_fork(philo, LEFT);
		lock_the_fork(philo, RIGHT);
	}
	else
	{
		lock_the_fork(philo, RIGHT);
		lock_the_fork(philo, LEFT);
	}
}

int	do_sleep(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	print_message(philo, SLEEP);
	msleep(philo->argv[TIME_SLEEP]);
	return (1);
}
