/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/17 14:19:02 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <semaphore.h>

# define INT_MAX 2147483647
# define LEFT 0
# define RIGHT 1
# define UNLOCK 0
# define LOCK 1
# define DIE 0
# define LIVE 1
# define START 0
# define RECENT 1
# define FALSE 0
# define TRUE 1
# define NUM_PHILO 0
# define TIME_DIE 1
# define TIME_EAT 2
# define TIME_SLEEP 3
# define MUST_EAT 4
# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define C_NRML "\033[0m"
# define C_GREN "\033[32m"
# define C_YLLW "\033[33m"
# define C_BLUE "\033[34m"
# define C_RED "\033[31m"

typedef struct timeval	t_time;

// typedef struct s_philo
// {
// 	int			id;
// 	int			*argv;
// 	t_time		*start_time;
// 	t_eat		eat_info;
// 	t_time		recent_time;
// }	t_philo;

typedef struct s_table
{
	int			argv[5];
	sem_t		*forks;
	// sem_t		*eat_enough;
	t_time		start_time;
	t_time		recent_time;
}	t_table;

/* philo.c */

/* init_struct */
int	init_argv(int argc, char *src[], int argv[][5]);
int	init_table(t_table *table);


#endif