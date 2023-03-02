/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:28:03 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/02 21:48:21 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_eat(t_philo *philo)
{
	if (am_i_dead(philo) == DEAD)
		return (0);
	pthread_mutex_lock(&philo->forks[LEFT].mutex);
	philo->forks[LEFT].state = LOCK;
	pthread_mutex_lock(&philo->forks[RIGHT].mutex);
	philo->forks[RIGHT].state = LOCK;
	printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(philo, START), philo->num);
	printf("%s%ld %d has taken a fork\n", C_NRML, get_time_diff(philo, START), philo->num);
	printf("%s%ld %d is eating\n", C_GREN, get_time_diff(philo, START), philo->num);

	usleep(philo->argv[TIME_EAT]); //usleep 정확도 체크 필요
	
	pthread_mutex_unlock(&philo->forks[LEFT].mutex);
	philo->forks[LEFT].state = UNLOCK;
	pthread_mutex_unlock(&philo->forks[RIGHT].mutex);
	philo->forks[RIGHT].state = UNLOCK;
	return (1);
}

int	do_sleep(t_philo *philo)
{
	if (am_i_dead(philo) == DEAD)
		return (0);
	printf("%s%ld %d is sleeping\n", C_YLLW, get_time_diff(philo, START), philo->num);
	usleep(philo->argv[TIME_SLEEP]); //usleep 정확도 체크 필요
	return (1);
}

int	do_think(t_philo *philo)
{
	if (am_i_dead(philo) == DEAD)
		return (0);
	printf("%s%ld %d is thinking\n", C_BLUE, get_time_diff(philo, START), philo->num);
	while (philo->forks[LEFT].state == LOCK && philo->forks[RIGHT].state == LOCK)
	{
		if (am_i_dead(philo) == DEAD)
			return (0);
	}
	return (1);
}
