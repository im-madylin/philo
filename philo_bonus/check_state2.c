/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:58:27 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:58:49 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	am_i_die(t_table *table)
{
	if (get_time_diff(table->recent_time) > table->argv[TIME_DIE])
	{
		sem_wait(table->print);
		printf("%s%ld %d died\n", C_RED, \
		get_time_diff(table->start_time), table->id);
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
		usleep(100);
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
