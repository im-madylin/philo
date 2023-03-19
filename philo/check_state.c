/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:31:52 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/17 12:00:02 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_you_die(t_philo *philo, int argv[])
{
	if (get_time_diff(philo->recent_time) > argv[TIME_DIE])
	{
		pthread_mutex_lock(&(philo->live->mutex));
		philo->live->is_live = DIE;
		printf("%s%ld %d died\n", C_RED, \
		get_time_diff(*(philo->start_time)), philo->id);
		pthread_mutex_unlock(&(philo->live->mutex));
		return (DIE);
	}
	return (LIVE);
}

int	check_eat_enough(t_table *table)
{
	if (check_eat_count(table) == TRUE)
	{
		pthread_mutex_lock(&(table->philos[1].live->mutex));
		table->philos[1].live->is_live = DIE;
		pthread_mutex_unlock(&(table->philos[1].live->mutex));
		return (TRUE);
	}
	else
		return (FALSE);
}

int	check_eat_count(t_table *table)
{
	t_philo	philo;
	int		is_enough;
	int		i;

	if (table->argv[MUST_EAT] == 0)
		return (FALSE);
	is_enough = TRUE;
	i = 1;
	while (i <= table->argv[NUM_PHILO])
	{
		philo = table->philos[i];
		pthread_mutex_lock(&(philo.eat_info.mutex));
		if (philo.eat_info.count < philo.argv[MUST_EAT])
			is_enough = FALSE;
		pthread_mutex_unlock(&(philo.eat_info.mutex));
		i++;
	}
	return (is_enough);
}
