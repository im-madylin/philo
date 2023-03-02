/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/02 13:47:52 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h> //
int	test(t_philo *philo)
{
	struct timeval end;

	printf("hi! im %d\n", philo->num);
	gettimeofday(&end, NULL);
	printf("%ld\n", (end.tv_sec - philo->start->tv_sec) + ((end.tv_usec - philo->start->tv_usec) / 1000000));
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (0);
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (0);
	if (init_argv(argc, argv, &(table->argv)) == 0)
		return (0); //유효하지 않은 인자 에러
	if (init_fork(&table) == -1)
		return (0); //malloc or 뮤텍스 생성실패
	if (init_philo(&table) == -1)
		return (0); //malloc 에러
	if (gettimeofday(&(table->start), NULL) == -1)
		return (0);
	if (init_thread(&table) == -1)
		return (0); //malloc 에러 or 스레드 생성실패
}
