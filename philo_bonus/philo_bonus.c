/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahlee <hahlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:20:25 by hahlee            #+#    #+#             */
/*   Updated: 2023/03/17 14:19:56 by hahlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (0);
	if (init_argv(argc, argv, &(table.argv)) == FALSE)
		return (0);
	init_sem(&table);

}

int	create_process(t_table *table)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < table->argv[NUM_PHILO])
	{
		pid = fork();
		if (pid < 0)
			return (FALSE); //처리 어케하지
		else if (pid == 0)
			//자식 함수
		else
			//부모 함수
	}
}
