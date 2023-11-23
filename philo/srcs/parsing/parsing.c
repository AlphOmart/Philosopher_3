/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:27:11 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/23 16:11:33 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_number(char **arg);
static int	is_uint(t_set *set);
static int	init_philo(t_set *set, t_philo **philo);

int	parsing(t_set *set, t_philo	**philo, char **arg)
{
	if (!is_number(arg))
		return (0);
	set->nbr = ft_atoll(arg[0]);
	set->t_die = ft_atoll(arg[1]);
	set->t_eat = ft_atoll(arg[2]);
	set->t_sleep = ft_atoll(arg[3]);
	if (arg[4])
	{
		set->meal_max = ft_atoll(arg[4]);
		if (set->meal_max <= 0)
			return (0);
	}
	else
		set->meal_max = -1;
	if (!is_uint(set))
		return (0);
	if (!init_philo(set, philo))
		return (0);
	return (1);
}

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
	if (set->nbr < 1)
		return (0);
	if (INT_MAX < set->t_die || set->t_die < 1)
		return (0);
	if (INT_MAX < set->t_eat || set->t_eat < 1)
		return (0);
	if (INT_MAX < set->t_sleep || set->t_sleep < 1)
		return (0);
	if (set->t_die < set->t_eat)
		set->t_eat = (set->t_die - set->t_sleep + 1);
	if (set->t_die < set->t_sleep)
		set->t_sleep = (set->t_die - set->t_eat + 1);
	if (INT_MAX < set->meal_max || set->meal_max < -1 || set->meal_max == 0)
		return (0);
	return (1);
}

static int	mutex_init(t_set *set, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < set->nbr)
	{
		if (pthread_mutex_init(&(*philo)[i].right_fork, NULL))
			return (0);
		(*philo)[i++].r_fork = false;
	}
	i = 0;
	while (i < set->nbr)
	{
		if (i != set->nbr - 1 && set->nbr != 1)
		{
			(*philo)[i].left_fork = &((*philo)[i + 1].right_fork);
			(*philo)[i].l_fork = &((*philo)[i + 1].r_fork);
		}
		else
		{
			(*philo)[i].left_fork = &((*philo)[0].right_fork);
			(*philo)[i].l_fork = &((*philo)[0].r_fork);
		}
		i++;
	}
	return (1);
}

static int	init_philo(t_set *set, t_philo **philo)
{
	int	i;

	i = 0;
	*philo = malloc(sizeof(t_philo) * set->nbr);
	if (!*philo)
		return (0);
	while (i < set->nbr)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].nbr = set->nbr;
		(*philo)[i].t_die = set->t_die;
		(*philo)[i].t_eat = set->t_eat;
		(*philo)[i].t_sleep = set->t_sleep;
		if ((set->nbr % 2) == 0)
			(*philo)[i].t_think = 0;
		else
			(*philo)[i].t_think = 5;
		(*philo)[i].meal_nbr = 0;
		i++;
	}
	if (!mutex_init(set, philo))
		return (0);
	return (1);
}
