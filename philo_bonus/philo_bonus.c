/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:20:25 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/20 15:52:34 by hahlee           ###   ########.fr       */
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
	pid = (pid_t)malloc(sizeof(pid_t) * table.argv[NUM_PHILO]);
	if (pid == NULL)
		return (0);
	if (create_process(&table, &pid) == FALSE)
		return (0); //처리 필요
	check_die(pid, table.argv[NUM_PHILO]);
}

int	create_process(t_table *table, pid_t **pid)
{
	int		i;

	i = 0;
	while (i <= table->argv[NUM_PHILO])
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
			return (FALSE); //처리 어케하지
		else if ((*pid)[i] == 0)
		{
			table->id = i + 1;
			do_action(table);
		}
		i++;
	}
	return (TRUE);
}

void	check_die(pid_t *pid, int num)
{
	int	state;
	int	i;

	i = 0;
	waitpid(-1, &state, 0);
	while (i < num)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}