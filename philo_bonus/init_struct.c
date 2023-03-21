/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:51:07 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 18:26:13 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_argv(int argc, char *src[], int argv[][6])
{
	int	tmp[5];
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (src[i][0] == '-' || ft_strlen(src[i]) > 10)
			return (FALSE);
		tmp[j] = ft_atoi(src[i]);
		if (tmp[j] == 0 || tmp[j] > INT_MAX)
			return (FALSE);
		i++;
		j++;
	}
	(*argv)[NUM_PHILO] = tmp[0];
	(*argv)[TIME_DIE] = tmp[1];
	(*argv)[TIME_EAT] = tmp[2];
	(*argv)[TIME_SLEEP] = tmp[3];
	(*argv)[MUST_EAT] = 0;
	(*argv)[PROCESS] = (*argv)[NUM_PHILO];
	if (argc == 6)
	{
		(*argv)[MUST_EAT] = tmp[4];
		(*argv)[PROCESS] += 1;
	}
	return (1);
}

void	init_table(t_table *table)
{
	sem_unlink("fork");
	sem_unlink("eat");
	sem_unlink("print");
	table->forks = sem_open("fork", O_CREAT | O_EXCL, 0644, table->argv[NUM_PHILO]);
	table->eat_enough = sem_open("eat", O_CREAT | O_EXCL, 0644, table->argv[NUM_PHILO]);
	table->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	gettimeofday(&(table->start_time), NULL);
	table->recent_time = table->start_time;
	table->id = 0;
}