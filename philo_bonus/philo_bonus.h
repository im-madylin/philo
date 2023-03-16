/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/16 20:45:31 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

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

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

typedef struct s_fork
{
	t_mutex	mutex;
	int		state;
}	t_fork;

typedef struct s_live
{
	t_mutex	mutex;
	int		is_live;
}	t_live;

typedef struct s_eat
{
	t_mutex	mutex;
	int		count;
}	t_eat;

typedef struct s_philo
{
	int			num;
	t_live		*live;
	t_fork		*forks[2];
	int			*argv;
	t_time		*start_time;
	t_eat		eat_info;
	t_time		recent_time;
	t_mutex		*print;
}	t_philo;

typedef struct s_table
{
	pthread_t	*threads;
	t_philo		*philos;
	t_fork		*forks;
	int			argv[5];
	t_time		start_time;
	t_live		live;
	t_mutex		print;
}	t_table;

/* philo.c */


#endif