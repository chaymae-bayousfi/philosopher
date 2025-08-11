/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:47:52 by cbayousf          #+#    #+#             */
/*   Updated: 2025/08/03 12:54:15 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_usleep(size_t ms, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		pthread_mutex_lock(&philo->prog->dead_lock);
		if (philo->prog->dead == 1)
		{
			pthread_mutex_unlock(&philo->prog->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->prog->dead_lock);
		usleep(500);
	}
	return (0);
}

void	print_stat(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->prog->dead_lock);
	if (!philo->prog->dead)
		printf("%zu %d %s\n", get_time() - philo->prog->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->prog->dead_lock);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	print_stat(philo, "has taken forks");
	pthread_mutex_lock(&philo->prog->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->prog->meal_lock);
	print_stat(philo, "is eating");
	ft_usleep(philo->prog->time_to_eat, philo);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	check_one_philo(t_philo *philo)
{
	if (philo->prog->num_of_philo == 1)
	{
		print_stat(philo, "has taken a fork");
		ft_usleep(philo->prog->time_to_die, philo);
		print_stat(philo, "is dead");
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->prog->dead_lock);
		if (philo->prog->dead == 1)
		{
			pthread_mutex_unlock(&philo->prog->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->prog->dead_lock);
		eat(philo);
		print_stat(philo, "is sleeping");
		ft_usleep(philo->prog->time_to_sleep, philo);
		print_stat(philo, "is thinking");
	}
	return (NULL);
}
