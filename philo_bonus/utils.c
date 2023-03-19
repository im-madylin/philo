/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:52:57 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/19 16:07:09 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	safe_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (0);
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

void	print_message(t_table *table, int flag)
{
	long	time;

	time = get_time_diff(table->start_time);
	if (flag == FORK)
		printf("%s%ld %d has taken a fork\n", C_NRML, time, table->id);
	else if (flag == EAT)
		printf("%s%ld %d is eating\n", C_GREN, time, table->id);
	else if (flag == SLEEP)
		printf("%s%ld %d is sleeping\n", C_YLLW, time, table->id);
	else if (flag == THINK)
		printf("%s%ld %d is thinking\n", C_BLUE, time, table->id);
}
