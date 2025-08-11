/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 10:58:32 by cbayousf          #+#    #+#             */
/*   Updated: 2025/08/03 10:24:21 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_putstr_fd("gettimeofday() error\n", 2);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	check_nb_meals(t_philo *philo)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while ((int)i < philo->prog->num_of_philo)
	{
		pthread_mutex_lock(&philo->prog->meal_lock);
		if (philo[i].meals_eaten >= philo->prog->num_times_to_eat
			&& philo->prog->num_times_to_eat != -1)
			count++;
		pthread_mutex_unlock(&philo->prog->meal_lock);
		i++;
	}
	pthread_mutex_lock(&philo->prog->dead_lock);
	if (count == i)
		philo->prog->dead = 1;
	pthread_mutex_unlock(&philo->prog->dead_lock);
}

void	monitor(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->prog->num_of_philo)
		{
			pthread_mutex_lock(&philo->prog->meal_lock);
			if ((get_time() - philo[i].last_meal) > philo->prog->time_to_die)
			{
				pthread_mutex_unlock(&philo->prog->meal_lock);
				pthread_mutex_lock(&philo->prog->dead_lock);
				philo->prog->dead = 1;
				printf("%zu %d is dead\n", get_time() - philo->prog->start_time,
					philo->id);
				pthread_mutex_unlock(&philo->prog->dead_lock);
				return ;
			}
			pthread_mutex_unlock(&philo->prog->meal_lock);
			i++;
		}
		check_nb_meals(philo);
		if (philo->prog->dead == 1)
			break ;
	}
}
