/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/07 22:08:27 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *table)
{
	while ()
	//필로들 돌면서 누구 하나 죽었으면 다 detach?
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	// table = (t_table *)malloc(sizeof(t_table));
	// if (table == NULL)
	// 	return (0);
	if (init_argv(argc, argv, &(table.argv)) == 0)
		return (0); //유효하지 않은 인자 에러
	if (init_fork(&table) == -1)
		return (0); //malloc or 뮤텍스 생성실패
	if (gettimeofday(&(table.start), NULL) == -1)
		return (0);
	if (init_philo(&table) == -1)
		return (0); //malloc 에러
	if (init_thread(&table) == -1)
		return (0); //malloc 에러 or 스레드 생성실패
	int i = 0;
	while (i < table.argv[NUM_PHILO])
	{
		pthread_join(table.threads[i], NULL);
		i++;
	}
}
