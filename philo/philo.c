/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/02/27 21:03:13 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h> //
int	initialize_t_argv(int argc, char *src[], int argv[][5])
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
		j++;
	}
	(*argv)[NUM_PHILO] = tmp[0];
	(*argv)[TIME_DIE] = tmp[1];
	(*argv)[TIME_EAT] = tmp[2];
	(*argv)[TIME_SLEEP] = tmp[3];
	(*argv)[MUST_EAT] = 0;
	if (argc == 6)
		(*argv)[MUST_EAT] = tmp[4];
	return (1);
}

// int	test(void *argv)
// {
// 	printf("")
// 	(void)argv;
// 	return (0);
// }

int	main(int argc, char *argv[])
{
	t_table	table;
	int	i;

	if (argc != 5 && argc != 6)
		return (0);
	if (initialize_t_argv(argc, argv, &(table.argv)) == 0)
		return (0);
	i = 0;
	while (i < table.argv[NUM_PHILO])
	{
		if (pthread_mutex_init(&(table.forks[i].mutex), NULL) != 0)
			return (0);
		i++;
	}
	// while (i < table.argv[NUM_PHILO])
	// {
	// 	if (pthread_create(&(table.philos[i]), NULL, (void *)test, NULL) != 0)
	// 		return (0); // 기존 스레드 종료?
	// 	i++;
	// }
}
