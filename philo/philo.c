/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:31:28 by hahlee            #+#    #+#             */
/*   Updated: 2023/02/11 21:00:10 by hahlee           ###   ########.fr       */
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

int	t_argv_init(int argc, char *src[], t_argv *argv)
{
	int	tmp;
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(src[i]) < 0)
			return (0);
		i++;
	} //int 범위 까지만 제한할 건지?
	argv->num_philo = ft_atoi(src[1]);
	argv->time_die = ft_atoi(src[2]);
	argv->time_eat = ft_atoi(src[3]);
	argv->time_sleep = ft_atoi(src[4]);
	argv->must_eat = 0;
	if (argc == 6)
		argv->must_eat = ft_atoi(src[5]);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc != 5 && argc != 6)
		return (0);
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (0);
	if (t_argv_init(argc, argv, &(table->argv)) == 0)
	{
		free(table);
		return (0);
	}
}