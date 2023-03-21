/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/21 20:28:59 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_struct(argc, argv, &table) == FALSE)
		return (0);
	// if (init_argv(argc, argv, &(table.argv)) == FALSE)
	// 	return (0);
	// if (init_fork(&table) == FALSE)
	// 	return (0);
	// init_print_live(&table);
	// if (init_philo(&table) == FALSE)
	// 	return (safe_free((void **)&(table.forks)));
	// gettimeofday(&(table.start_time), NULL);
	// if (init_thread(&table) == FALSE)
	// 	return (safe_free((void **)&(table.forks)), \
	// 	safe_free((void **)&(table.philos)));
		
	check_die(&table);
	safe_free((void **)&(table.forks));
	safe_free((void **)&(table.philos));
	safe_free((void **)&(table.threads));
	return (0);
}

int	init_struct(int argc, char *argv[], t_table *table)
{
	if (init_argv(argc, argv, &(table->argv)) == FALSE)
		return (FALSE);
	if (init_fork(table) == FALSE)
		return (FALSE);
	init_print_live(table);
	if (init_philo(table) == FALSE)
		return (safe_free((void **)table->forks), FALSE);
	gettimeofday(&(table->start_time), NULL);
	if (init_thread(table) == FALSE)
		return (safe_free((void **)table->forks), \
		safe_free((void **)table->philos), FALSE);
	return (TRUE);
}
