/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:14:11 by hahlee            #+#    #+#             */
/*   Updated: 2023/02/14 20:42:09 by hahlee           ###   ########.fr       */
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

void	*ft_malloc(size_t size)
{
	void	*tmp;

	tmp = malloc(size);
	if (tmp == NULL)
		exit(1);
	return (tmp);
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
