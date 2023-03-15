/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:31:52 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/15 19:24:49 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	are_you_die(t_philo *philo, int argv[])
{
	if (get_time_diff(philo->recent_time) > argv[TIME_DIE])
	{
		pthread_mutex_lock(&(philo->live->mutex));
		philo->live->is_live = DIE;
		printf("%s%ld %d died\n", C_RED, get_time_diff(*(philo->start_time)), philo->num);
		pthread_mutex_unlock(&(philo->live->mutex));
		return (DIE);
	}
	return (LIVE);
}

int	check_eat_enough(t_philo *philo)
{
	if (check_eat_count(philo) == TRUE)
	{
		pthread_mutex_lock(&(philo->live->mutex));
		philo->live->is_live = DIE;
		pthread_mutex_unlock(&(philo->live->mutex));
		return (TRUE);
	}
	else
		return (FALSE);
}

int	check_eat_count(t_philo *philo)
{
	int	is_enough;

	is_enough = FALSE;
	if (philo->argv[MUST_EAT] == 0)
		return (FALSE);
	pthread_mutex_lock(&(philo->eat_info.mutex));
	if (philo->eat_info.count >= philo->argv[MUST_EAT])
		is_enough = TRUE;
	pthread_mutex_unlock(&(philo->eat_info.mutex));
	return (is_enough);
}
