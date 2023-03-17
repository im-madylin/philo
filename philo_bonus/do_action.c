/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:12:04 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/17 14:32:43 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	do_action(t_table *table)
{
	while (am_i_die(table) == LIVE)
	{
		if (do_think(table) == 0)
			return (0);
		if (do_eat(table) == 0)
			return (0);
		if (do_sleep(table) == 0)
			return (0);
	}
	return (0);
}

int	am_i_die(t_table *table)
{
	if (get_time_diff(table->recent_time) > argv[TIME_DIE])
	{
		printf("%s%ld %d died\n", C_RED, \
		get_time_diff(*(philo->start_time)), philo->id);
		return (DIE);
	}
	return (LIVE);
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
