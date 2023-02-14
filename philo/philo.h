/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:21 by hahlee            #+#    #+#             */
/*   Updated: 2023/02/14 20:42:26 by hahlee           ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;

typedef struct s_argv
{
	unsigned int	num_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	unsigned int	must_eat;
}	t_argv;

typedef struct s_fork
{
	t_mutex	mutex;
	int		state;
}	t_fork;

typedef struct s_philo
{
	int			num;
	pthread_t	thread;
	int			is_alive;
	t_fork		*forks[2];
}	t_philo;

typedef	struct s_table
{
	t_philo	*philos;
	t_fork	*forks;
	t_argv	argv;
}	t_table;


/* utils.c */
int	ft_atoi(const char *str);
void	*ft_malloc(size_t size);
int	safe_free(void **ptr);
size_t	ft_strlen(const char *s);
