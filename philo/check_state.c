/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:31:52 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/15 16:04:47 by hahlee           ###   ########.fr       */
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

int	are_you_die(t_philo *philo, int argv[])
{
	if (get_time_diff(philo->recent) > argv[TIME_DIE])
	{
		pthread_mutex_lock(&(philo->live->mutex));
		philo->live->is_live = DIE;
		printf("%s%ld %d died\n", C_RED, get_time_diff(*(philo->start)), philo->num);
		pthread_mutex_unlock(&(philo->live->mutex));
		return (DIE);
	}
	return (LIVE);
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
		// usleep((ms - diff) * 1000);
		usleep(100);
		gettimeofday(&end, NULL);
		diff = time_to_ms(end) - time_to_ms(start);
	}
	return (0);
}

int	time_to_ms(t_time time)
{
	const time_t sec_to_ms = time.tv_sec * 1000;
	const suseconds_t usec_to_ms = time.tv_usec / 1000;
	
	return (sec_to_ms + usec_to_ms);
}

long	get_time_diff(t_time start)
{
	t_time	cur;

	gettimeofday(&cur, NULL);
	return (time_to_ms(cur) - time_to_ms(start));
}
