/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:31:52 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/02 21:43:41 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_dead(t_philo *philo)
{
	if (get_time_diff(philo, RECENT) > philo->argv[TIME_DIE])
	{
		printf("%s%ld %d died\n", C_RED, get_time_diff(philo, START), philo->num);
		philo->is_live = DEAD;
		return (DEAD);
	}
	return (LIVE);
}

long	get_time_diff(t_philo *philo, int flag)
{
	t_time	cur;

	gettimeofday(&cur, NULL);
	if (flag == START)
	{
		return (((cur.tv_sec - philo->start->tv_sec) * 1000) + \
		((cur.tv_usec - philo->start->tv_usec) / 1000));
	}
	else if (flag == RECENT)
	{
		return (((cur.tv_sec - philo->recent.tv_sec) * 1000) + \
		((cur.tv_usec - philo->recent.tv_usec) / 1000));
	}
	return (0);
}
