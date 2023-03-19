/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:12:04 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/19 17:26:23 by hahlee           ###   ########.fr       */
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

int	do_eat(t_table *table)
{
	pick_up_fork(table);
	if (am_i_die(table) == DIE)
		return (0);
	print_message(table, EAT);
	gettimeofday(&(table->recent_time), NULL);
	msleep(table->argv[TIME_EAT]);
	// add_eat_count(philo);
	put_down_fork(table);
	return (1);
}

void	pick_up_fork(t_table *table)
{
	lock_the_fork(table);
	lock_the_fork(table); //한명이면 여기 안타야할듯
}

void	lock_the_fork(t_table *table)
{
	if (am_i_die(table) == DIE)
		return ;
	sem_wait(table->forks);
	print_message(table, FORK);
}

void	put_down_fork(t_table *table)
{
	unlock_the_fork(table);
	unlock_the_fork(table);
}

void	unlock_the_fork(t_table *table)
{
	if (am_i_die(table) == DIE)
		return ;
	sem_post(table->forks);
}

int	do_sleep(t_table *table)
{
	if (am_i_die(table) == DIE)
		return (0);
	print_message(table, SLEEP);
	msleep(table->argv[TIME_SLEEP]);
	return (1);
}

int	am_i_die(t_table *table)
{
	if (get_time_diff(table->recent_time) > table->argv[TIME_DIE])
	{
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
