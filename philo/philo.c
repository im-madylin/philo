/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/13 16:34:12 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_table *table)
{
	int	i;
	int	j;

	j = 1;
	while (1)
	{
		i = 1;
		while (i <= table->argv[NUM_PHILO])
		{
			// if (table->is_live == DIE)
			// {
			// 	// while (j <= table->argv[NUM_PHILO])
			// 	// {
			// 	// 	table->philos[j].is_live = DIE;
			// 	// 	j++;
			// 	// }
			// 	i = 1;
			// 	while (i <= table->argv[NUM_PHILO])
			// 	{
			// 		pthread_join(table->threads[i], NULL);
			// 		i++;
			// 	}
			// 	return (0);
			// }
			if (are_you_die(&(table->philos[i])) == DIE)
			{
				// while (j <= table->argv[NUM_PHILO])
				// {
				// 	table->philos[j].is_live = DIE;
				// 	j++;
				// }
				i = 1;
				while (i <= table->argv[NUM_PHILO])
				{
					pthread_join(table->threads[i], NULL);
					i++;
				}
				return (0);
			}
			usleep(300);
			i++;
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == 0)
		return (0); //유효하지 않은 인자 에러
	if (init_fork(&table) == -1)
		return (0); //malloc or 뮤텍스 생성실패
	if (init_philo(&table) == -1)
		return (0); //malloc 에러
	gettimeofday(&(table.start), NULL);
	if (init_thread(&table) == -1)
		return (0); //malloc 에러 or 스레드 생성실패
	check_die(&table);
	return (0);
}
