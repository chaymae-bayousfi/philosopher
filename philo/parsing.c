/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbayousf <cbayousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 14:13:54 by cbayousf          #+#    #+#             */
/*   Updated: 2025/08/01 15:33:39 by cbayousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] == '+')
		i++;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	pars_philo(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 6)
		return (ft_putstr_fd("too many args !\n", 2), 1);
	else if (ac < 5)
		return (ft_putstr_fd("need more args !\n", 2), 1);
	while (i < ac)
	{
		if (check_args(av[i]) || ft_atoi(av[i]) <= 0)
			return (ft_putstr_fd("invalide args !\n", 2), 1);
		i++;
	}
	return (0);
}
