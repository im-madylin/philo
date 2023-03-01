/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/01 20:55:40 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#define INT_MAX 2147483647
#define LEFT 0
#define RIGHT 1
#define UNLOCK 0
#define LOCK 1
#define DEAD 0
#define LIVE 1
#define NUM_PHILO 0
#define TIME_DIE 1
#define TIME_EAT 2
#define TIME_SLEEP 3
#define MUST_EAT 4

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex	mutex;
	int		state;
}	t_fork;

typedef struct s_philo
{
	int			num;
	int			is_alive;
	t_fork		forks[2];
}	t_philo;

typedef	struct s_table
{
	pthread_t	*threads;
	t_philo		*philos;
	t_fork		*forks;
	int	argv[5];
}	t_table;

/* philo.c */
int	init_argv(int argc, char *src[], int argv[][5]);
int	init_fork(t_table **table);
int	init_philo(t_table **table);
int	init_thread(t_table **table);
int	test(t_philo *philo);


/* utils.c */
int	ft_atoi(const char *str);
void	*ft_malloc(size_t size);
int	safe_free(void **ptr, int result);
size_t	ft_strlen(const char *s);
