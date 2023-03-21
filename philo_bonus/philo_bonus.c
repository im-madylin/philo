/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:20:25 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 17:03:34 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	pid_t	*pid;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == FALSE)
		return (0);
	init_table(&table);
	pid = (pid_t *)malloc(sizeof(pid_t) * (table.argv[PROCESS]));
	if (pid == NULL)
		return (0);
	if (create_process(&table, &pid) == FALSE)
		return (kill_process(&pid, table.argv[PROCESS]));
	check_die(&pid, table.argv[PROCESS]);
	sem_close(table.forks);
	sem_close(table.eat_enough);
}

int	create_process(t_table *table, pid_t **pid)
{
	int		i;

	i = 0;
	while (i < table->argv[NUM_PHILO])
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
			return (FALSE); //처리 어케하지
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
		return (FALSE);
	else if ((*pid)[num] == 0)
	{
		check_eat_enough(table);
	}
	return (TRUE);
}

void	check_die(pid_t **pid, int num)
{
	int	state;

	waitpid(-1, &state, 0);
	kill_process(pid, num);
}

int	kill_process(pid_t **pid, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		kill((*pid)[i], SIGKILL);
		i++;
	}
	safe_free((void **)pid);
	return (0);
}