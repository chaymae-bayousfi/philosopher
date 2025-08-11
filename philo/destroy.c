/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:35:30 by cbayousf          #+#    #+#             */
/*   Updated: 2025/08/03 10:25:05 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->num_of_philo)
		pthread_mutex_destroy(&prog->fork[i++]);
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->dead_lock);
}

void	free_data(t_program *prog, t_philo *philo)
{
	int	i;

	i = 0;
	if (philo)
		free(philo);
	if (prog)
	{
		if (prog->fork)
			free(prog->fork);
		free(prog);
	}
}
