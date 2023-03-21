/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:59:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:51:54 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pick_up_fork(t_table *table)
{
	if (lock_the_fork(table) == DIE)
		return (DIE);
	if (table->argv[NUM_PHILO] == 1)
		spend_time_when_alone(table);
	else
		if (lock_the_fork(table) == DIE)
			return (DIE);
	return (LIVE);
}

int	lock_the_fork(t_table *table)
{
	if (am_i_die(table) == DIE)
		return (DIE);
	sem_wait(table->forks);
	print_message(table, FORK);
	return (LIVE);
}

void	spend_time_when_alone(t_table *table)
{
	int	spend_time;
	int	spare_time;

	spend_time = get_time_diff(table->start_time);
	spare_time = table->argv[TIME_DIE] - spend_time + 1;
	msleep(spare_time);
}

int	put_down_fork(t_table *table)
{
	if (unlock_the_fork(table) == DIE)
		return (DIE);
	if (unlock_the_fork(table) == DIE)
		return (DIE);
	return (LIVE);
}

int	unlock_the_fork(t_table *table)
{
	if (am_i_die(table) == DIE)
		return (DIE);
	sem_post(table->forks);
	return (LIVE);
}
