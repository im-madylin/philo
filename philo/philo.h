/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/16 15:33:46 by hahlee           ###   ########.fr       */
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
#define DIE 0
#define LIVE 1
#define START 0
#define RECENT 1
#define FALSE 0
#define	TRUE 1
#define NUM_PHILO 0
#define TIME_DIE 1
#define TIME_EAT 2
#define TIME_SLEEP 3
#define MUST_EAT 4
#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
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

typedef struct s_live
{
	t_mutex	mutex;
	int	is_live;
}	t_live;

typedef struct	s_eat
{
	t_mutex	mutex;
	int	count;
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

typedef	struct s_table
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
int		check_die(t_table *table);

/* do_action.c */
int		do_action(t_philo *philo);
int		do_think(t_philo *philo);
int		do_eat(t_philo *philo);
void	add_eat_count(t_philo *philo);
int		do_sleep(t_philo *philo);

/* do_action2.c */
void	pick_up_fork(t_philo *philo);
void	spend_time_when_alone(t_philo *philo);
void	lock_the_fork(t_philo *philo, int flag);
void	put_down_fork(t_philo *philo);
void	unlock_the_fork(t_philo *philo, int flag);

/* check_state.c */
int		are_you_die(t_philo *philo, int argv[]);
int		check_eat_enough(t_table *table);
int		check_eat_count(t_table *table);

/* check_state2.c */
int		am_i_die(t_philo *philo);
int		msleep(int ms);
long	get_time_diff(t_time start_time);
int		time_to_ms(t_time time);

/* init_struct.c */
int		init_argv(int argc, char *src[], int argv[][5]);
int		init_fork(t_table *table);
void	init_print_live(t_table *table);
int		init_philo(t_table *table);
int		init_thread(t_table *table);

/* utils.c */
int		ft_atoi(const char *str);
void	*ft_malloc(size_t size);
int		safe_free(void **ptr);
size_t	ft_strlen(const char *s);
void	print_message(t_philo *philo, int flag);
