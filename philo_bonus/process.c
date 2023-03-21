/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:56:13 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:57:39 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_process(t_table *table, pid_t **pid)
{
	int		i;

	i = 0;
	while (i < table->argv[NUM_PHILO])
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
			return (i);
		else if ((*pid)[i] == 0)
		{
			table->id = i + 1;
			sem_wait(table->eat_enough);
			do_action(table);
		}
		i++;
	}
	return (create_eat_monitoring(table, pid));
}

int	create_eat_monitoring(t_table *table, pid_t **pid)
{
	int	num;

	num = table->argv[NUM_PHILO];
	(*pid)[num] = fork();
	if ((*pid)[num] < 0)
		return (num);
	else if ((*pid)[num] == 0)
		check_eat_enough(table);
	return (-1);
}

int	kill_process(t_table *table, pid_t **pid)
{
	int	i;

	i = 0;
	while (i < table->argv[PROCESS])
	{
		kill((*pid)[i], SIGKILL);
		i++;
	}
	safe_free((void **)pid);
	close_sem(table);
	return (0);
}

int	close_sem(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->eat_enough);
	sem_close(table->print);
	return (0);
}
