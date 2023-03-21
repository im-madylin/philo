/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:12:04 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:19:49 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	do_action(t_table *table)
{
	int	eat_count;

	eat_count = 0;
	if (table->id % 2 == 0)
		msleep(5);
	while (am_i_die(table) == LIVE)
	{
		if (do_think(table) == 0)
			exit(0);
		if (do_eat(table, &eat_count) == 0)
			exit(0);
		if (do_sleep(table) == 0)
			exit(0);
	}
	exit(0);
}

int	do_think(t_table *table)
{
	int	*argv;
	int	think_time;

	if (am_i_die(table) == DIE)
		return (0);
	print_message(table, THINK);
	argv = table->argv;
	think_time = argv[TIME_DIE] - (argv[TIME_EAT] + argv[TIME_SLEEP] + 50);
	if (think_time <= 0)
		return (1);
	msleep(think_time);
	return (1);
}

int	do_eat(t_table *table, int *eat_count)
{
	if (pick_up_fork(table) == DIE)
		return (0);
	if (am_i_die(table) == DIE)
		return (0);
	print_message(table, EAT);
	gettimeofday(&(table->recent_time), NULL);
	msleep(table->argv[TIME_EAT]);
	add_eat_count(table, eat_count);
	if (put_down_fork(table) == DIE)
		return (0);
	return (1);
}

void	add_eat_count(t_table *table, int *eat_count)
{
	*eat_count += 1;
	if (*eat_count == table->argv[MUST_EAT])
		sem_post(table->eat_enough);
}

int	do_sleep(t_table *table)
{
	if (am_i_die(table) == DIE)
		return (0);
	print_message(table, SLEEP);
	msleep(table->argv[TIME_SLEEP]);
	return (1);
}
