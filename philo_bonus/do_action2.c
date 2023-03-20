/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:59:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/20 17:05:04 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	pick_up_fork(t_table *table)
{
	if (lock_the_fork(table) == DIE)
		return (DIE);
	if (lock_the_fork(table) == DIE) //한명이면 여기 안타야할듯
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
