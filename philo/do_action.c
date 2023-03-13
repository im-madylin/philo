/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:28:03 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/13 20:22:24 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	do_action(t_philo *philo)
{
	if (philo->num % 2 == 0)
		msleep(100);
	while (*(philo->is_live) == LIVE)
	{
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
		return (0);
	print_message(philo, EAT);
	gettimeofday(&(philo->recent), NULL);
	msleep(philo->argv[TIME_EAT]);
	put_down_fork(philo);
	return (1);
}

int	pick_up_fork(t_philo *philo)
{
	if (philo->num % 2 != 0)
	{
		if (pick_up_left_fork(philo) == 0 || pick_up_right_fork(philo) == 0)
			return (0);
	}
	else
	{
		if (pick_up_right_fork(philo) == 0 || pick_up_left_fork(philo) == 0)
			return (0);
	}
	return (1);
}

int	do_sleep(t_philo *philo)
{
	if (am_i_die(philo) == DIE)
		return (0);
	print_message(philo, SLEEP);
	msleep(philo->argv[TIME_SLEEP]);
	return (1);
}
