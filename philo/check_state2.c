/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:23:04 by hahlee            #+#    #+#             */
/*   Updated: 2023/04/04 16:13:59 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_die(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&(philo->live->mutex));
	state = philo->live->is_live;
	pthread_mutex_unlock(&(philo->live->mutex));
	return (state);
}

int	msleep(int ms)
{
	t_time	start;
	t_time	end;
	int		diff;

	diff = 0;
	gettimeofday(&start, NULL);
	while (diff < ms)
	{
		usleep(500);
		gettimeofday(&end, NULL);
		diff = time_to_ms(end) - time_to_ms(start);
	}
	return (0);
}

long	get_time_diff(t_time start)
{
	t_time	cur;

	gettimeofday(&cur, NULL);
	return (time_to_ms(cur) - time_to_ms(start));
}

int	time_to_ms(t_time time)
{
	time_t		sec_to_ms;
	suseconds_t	usec_to_ms;

	sec_to_ms = time.tv_sec * 1000;
	usec_to_ms = time.tv_usec / 1000;
	return (sec_to_ms + usec_to_ms);
}
