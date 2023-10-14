/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:27:11 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 12:35:32 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char **arg)
{
	int	i;
	int	j;

	i = -1;
	while (arg[++i])
	{
		j = 0;
		while (is_white_space(arg[i][j]))
			j++;
		if (arg[i][j] == '+' || arg[i][j] == '-')
			j++;
		while (arg[i][j])
		{
			if (arg[i][j] < '0' || '9' < arg[i][j])
				return (0);
			j++;
		}
	}
	return (1);
}

static int	is_uint(t_set *set)
{
	if (INT_MAX < set->nbr || set->nbr < 1)
		return (0);
	if (INT_MAX < set->t_die || set->t_die < 1)
		return (0);
	if (INT_MAX < set->t_eat || set->t_eat < 1)
		return (0);
	if (INT_MAX < set->t_sleep || set->t_sleep < 1)
		return (0);
	if (INT_MAX < set->eat_nbr || set->eat_nbr < -1 || set->eat_nbr == 0)
		return (0);
	return (1);
}

int	parsing(t_set *set, char **arg)
{
	if (!is_number(arg))
		return (0);
	set->nbr = ft_atoll(arg[0]);
	set->t_die = ft_atoll(arg[1]);
	set->t_eat = ft_atoll(arg[2]);
	set->t_sleep = ft_atoll(arg[3]);
	if (arg[4])
	{
		set->eat_nbr = ft_atoll(arg[4]);
		if (set->eat_nbr <= 0)
			return (0);
	}
	else
		set->eat_nbr = -1;
	if (!is_uint(set))
		return (0);
	return (1);
}
