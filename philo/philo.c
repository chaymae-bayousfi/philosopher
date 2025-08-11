/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:08:11 by cbayousf          #+#    #+#             */
/*   Updated: 2025/08/04 10:04:31 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*initialise_philo(t_program *prog)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * prog->num_of_philo);
	if (!philo)
		return (NULL);
	while (i < prog->num_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = prog->start_time;
		philo[i].r_fork = &prog->fork[i];
		philo[i].l_fork = &prog->fork[(i + 1) % prog->num_of_philo];
		philo[i].prog = prog;
		i++;
	}
	return (philo);
}

t_program	*initialise_mutex(t_program **prog)
{
	int		i;

	i = 0;
	while (i < (*prog)->num_of_philo)
	{
		if (pthread_mutex_init(&(*prog)->fork[i], NULL) != 0)
			return (free((*prog)->fork), free(*prog), NULL);
		i++;
	}
	if (pthread_mutex_init(&(*prog)->write_lock, NULL) != 0)
		return (free((*prog)->fork), free(*prog), NULL);
	if (pthread_mutex_init(&(*prog)->meal_lock, NULL) != 0)
		return (free((*prog)->fork), free(*prog), NULL);
	if (pthread_mutex_init(&(*prog)->dead_lock, NULL) != 0)
		return (free((*prog)->fork), free(*prog), NULL);
	return (*prog);
}

t_program	*initialise_variable(int ac, char **av)
{
	t_program	*prog;
	int			i;

	i = 0;
	prog = malloc(sizeof(t_program));
	if (!prog)
		return (NULL);
	prog->start_time = get_time();
	prog->num_of_philo = ft_atoi(av[1]);
	prog->num_of_forks = ft_atoi(av[1]);
	prog->time_to_die = ft_atoi(av[2]);
	prog->time_to_eat = ft_atoi(av[3]);
	prog->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		prog->num_times_to_eat = ft_atoi(av[5]);
	else
		prog->num_times_to_eat = -1;
	prog->dead = 0;
	prog->fork = malloc(sizeof(pthread_mutex_t) * prog->num_of_philo);
	if (!prog->fork)
		return (free(prog), NULL);
	return (initialise_mutex(&prog));
}

void	start_threads(t_program *prog, t_philo *philo)
{
	int				i;

	i = 0;
	if (check_one_philo(philo))
		return ;
	while (i < prog->num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return ;
		i++;
	}
	monitor(philo);
	i = 0;
	while (i < prog->num_of_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			return ;
		i++;
	}
}
void ff()
{
	system("leaks philo");
}
int	main(int ac, char **av)
{
	t_program	*prog;

	// atexit(ff);
	if (pars_philo(ac, av))
		return (1);
	prog = initialise_variable(ac, av);
	if (!prog)
		return (destroy_mutex(prog), 1);
	prog->philo = initialise_philo(prog);
	if (!prog->philo)
		return (free_data(prog, prog->philo), destroy_mutex(prog), 1);
	start_threads(prog, prog->philo);
	// destroy_mutex(prog);
	free_data(prog, prog->philo);
}
