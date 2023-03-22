/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_resource.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:33:40 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/22 19:18:28 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 1;
	while (i <= table->argv[NUM_PHILO])
	{
		pthread_mutex_destroy(&(table->forks[i].mutex));
		pthread_mutex_destroy(table->philos[i++].eat_info.mutex);
		i++;
	}
	pthread_mutex_destroy(&(table->live.mutex));
	pthread_mutex_destroy(&(table->print));
}

void	free_all(t_table *table)
{
	safe_free((void **)&(table->forks));
	free_eat_info(table);
	safe_free((void **)&(table->philos));
	safe_free((void **)&(table->threads));
}

void	free_eat_info(t_table *table)
{
	int	i;

	i = 1;
	while (i <= table->argv[NUM_PHILO])
	{
		safe_free((void **)&(table->philos[i].eat_info.mutex));
		i++;
	}
}

int	safe_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (0);
}
