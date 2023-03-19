/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:20:25 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/19 19:46:25 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == FALSE)
		return (0);
	init_table(&table);
	create_process(&table);

}

int	create_process(t_table *table)
{
	pid_t	pid;
	int		i;

	i = 1;
	while (i <= table->argv[NUM_PHILO])
	{
		pid = fork();
		if (pid < 0)
			return (FALSE); //처리 어케하지
		else if (pid == 0)
		{
			table->id = i;
			do_action(table);
			break ;
		}
		i++;
	}
	check_die();
	return (0);
}

void	check_die(void)
{
	int	state;

	waitpid(-1, &state, 0);
	kill(0, SIGKILL);
}