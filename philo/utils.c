/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:14:11 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/22 18:34:38 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
	unsigned long long	max;
	int					sign;
	int					i;

	result = 0;
	max = 9223372036854775808ULL;
	sign = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && result <= max)
		result = result * 10 + (str[i++] - '0');
	if (result >= max && sign == 1)
		return (-1);
	else if (result > max && sign == -1)
		return (0);
	return (result * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		count++;
		i++;
	}
	return (count);
}

void	print_message(t_philo *philo, int flag)
{
	long	time;

	pthread_mutex_lock(philo->print);
	pthread_mutex_lock(&(philo->live->mutex));
	if (philo->live->is_live == DIE)
	{
		pthread_mutex_unlock(&(philo->live->mutex));
		pthread_mutex_unlock(philo->print);
		return ;
	}
	pthread_mutex_unlock(&(philo->live->mutex));
	time = get_time_diff(*(philo->start_time));
	if (flag == FORK)
		printf("%s%ld %d has taken a fork\n", C_NRML, time, philo->id);
	else if (flag == EAT)
		printf("%s%ld %d is eating\n", C_GREN, time, philo->id);
	else if (flag == SLEEP)
		printf("%s%ld %d is sleeping\n", C_YLLW, time, philo->id);
	else if (flag == THINK)
		printf("%s%ld %d is thinking\n", C_BLUE, time, philo->id);
	pthread_mutex_unlock(philo->print);
}
