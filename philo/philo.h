/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/07 16:35:07 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

#define INT_MAX 2147483647
#define LEFT 0
#define RIGHT 1
#define UNLOCK 0
#define LOCK 1
#define DEAD 0
#define LIVE 1
#define START 0
#define RECENT 1
#define NUM_PHILO 0
#define TIME_DIE 1
#define TIME_EAT 2
#define TIME_SLEEP 3
#define MUST_EAT 4
#define C_NRML "\033[0m"
#define C_GREN "\033[32m"
#define C_YLLW "\033[33m"
#define C_BLUE "\033[34m"
#define C_RED "\033[31m"

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

typedef struct s_fork
{
	t_mutex	mutex;
	int		state;
}	t_fork;

typedef struct s_philo
{
	int			num;
	int			is_live;
	t_fork		*forks[2];
	int			*argv;
	t_time		*start;
	t_time		recent;
}	t_philo;

typedef	struct s_table
{
	pthread_t	*threads;
	t_philo		*philos;
	t_fork		*forks;
	int			argv[5];
	t_time		start;
}	t_table;

/* philo.c */

/* do_action.c */
int	do_action(t_philo *philo);
int	do_eat(t_philo *philo);
int	do_sleep(t_philo *philo);
int	do_think(t_philo *philo);

/* check_state.c */
int	am_i_die(t_philo *philo);
long	get_time_diff(t_philo *philo, int flag);

/* init_struct.c */
int	init_argv(int argc, char *src[], int argv[][5]);
int	init_fork(t_table *table);
int	init_philo(t_table *table);
int	init_thread(t_table *table);

/* utils.c */
int	ft_atoi(const char *str);
void	*ft_malloc(size_t size);
int	safe_free(void **ptr, int result);
size_t	ft_strlen(const char *s);
