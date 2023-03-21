/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:20:25 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:10:46 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	pid_t	*pid;
	int		i;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == FALSE)
		return (0);
	init_table(&table);
	pid = (pid_t *)malloc(sizeof(pid_t) * (table.argv[PROCESS]));
	if (pid == NULL)
		return (close_sem(&table));
	i = create_process(&table, &pid);
	if (i != -1)
	{
		table.argv[PROCESS] = i;
		return (kill_process(&table, &pid));
	}
		
	check_die(&table, &pid);
	return (0);
}

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

void	check_die(t_table *table, pid_t **pid)
{
	int	state;

	waitpid(-1, &state, 0);
	kill_process(table, pid);
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