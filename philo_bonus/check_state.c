/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 19:58:12 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 19:59:02 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_die(t_table *table, pid_t **pid)
{
	int	state;

	waitpid(-1, &state, 0);
	kill_process(table, pid);
}

int	check_eat_enough(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->argv[NUM_PHILO])
	{
		sem_wait(table->eat_enough);
		i++;
	}
	exit(0);
}
