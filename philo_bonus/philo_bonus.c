/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:20:25 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:59:10 by hahlee           ###   ########.fr       */
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
	if (init_argv(argc, argv, &(table.argv), 0) == FALSE)
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
