/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/02/14 20:58:19 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h> //
int	initialize_t_argv(int argc, char *src[], t_argv *argv)
{
	int	tmp[5];
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < argc)
	{
		if (src[i][0] == '-' || ft_strlen(src[i]) > 10)
			return (0);
		tmp[j] = ft_atoi(src[i]);
		printf("%d\n", tmp[j]);
		if (tmp[j] == 0 || tmp[j] > INT_MAX)
			return (0);
		i++;
	}
	argv->num_philo = tmp[0];
	argv->time_die = tmp[1];
	argv->time_eat = tmp[2];
	argv->time_sleep = tmp[3];
	argv->must_eat = 0;
	if (argc == 6)
		argv->must_eat = tmp[4];
	return (1);
}

int	test(void *argv)
{
	// t_table	**table;

	// table = (t_table)argv
	(void)argv;
	return (0);
}

int	create_monitoring_thread(t_table **table)
{
	pthread_t	monitoring;

	(void)table;
	if (pthread_create(&monitoring, NULL, (void *)test, NULL) != 0)
		return (0);
	return (0);
}

int	main(int argc, char *argv[])
{
	// t_table	*table;
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	// table = (t_table *)ft_malloc(sizeof(t_table));
	// if (initialize_t_argv(argc, argv, &(table->argv)) == 0)
	if (initialize_t_argv(argc, argv, &table.argv) == 0)
		// return (safe_free(&table));
		return (0);
	printf("%d, %d, %d, %d, %d\n", table.argv.num_philo, table.argv.time_die, table.argv.time_eat, table.argv.time_sleep, table.argv.must_eat);
	
}