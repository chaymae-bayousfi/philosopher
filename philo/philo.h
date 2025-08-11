/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:10:35 by cbayousf          #+#    #+#             */
/*   Updated: 2025/08/03 12:40:26 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo	t_philo;

typedef struct s_program
{
	int				num_of_philo;
	int				num_of_forks;
	int				num_times_to_eat;
	int				dead;
	size_t			time_to_sleep;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*fork;
}	t_program;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_program		*prog;
}	t_philo;

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		pars_philo(int ac, char **av);
void	*routine(void *prog);
size_t	get_time(void);
void	monitor(t_philo *philo);
void	destroy_mutex(t_program *prog);
void	free_data(t_program *prog, t_philo *philo);
int		check_one_philo(t_philo *philo);
#endif