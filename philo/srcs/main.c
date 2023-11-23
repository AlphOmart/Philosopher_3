/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/23 16:40:33 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	checker(t_table	*table, t_set *set)
{
	t_philo		*philo;
	int			enought;
	int			i;

	i = -1;
	enought = 0;
	while (++i < set->nbr)
	{
		philo = &table->philo[i];
		if ((uint_fast64_t)set->t_die < timestamp() - philo->last_meal)
		{
			printf(DEF_PROMT"%s\n", timestamp() - \
					table->t_start, philo->id, DIED_MESS);
			return (0);
		}
		if (set->meal_max > 0 && set->meal_max <= philo->meal_nbr)
			enought++;
	}
	if (set->nbr <= enought)
		return (0);
	return (1);
}

static void	thread_monitoring(t_table *table, t_set *set)
{
	while (42)
	{
		pthread_mutex_lock(&table->manage);
		if (!checker(table, set))
		{
			table->dead = true;
			pthread_mutex_unlock(&table->manage);
			break ;
		}
		pthread_mutex_unlock(&table->manage);
		usleep(set->t_die * 0.5);
	}
}

static void	ft_free(t_table *table, t_set *set)
{
	int	i;

	i = -1;
	while (++i < set->nbr)
		pthread_mutex_destroy(&table->philo[i].right_fork);
	pthread_mutex_destroy(&table->synch);
	pthread_mutex_destroy(&table->manage);
	free(table->philo);
}

void	*routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *) arg;
	pthread_mutex_lock(&this->table->synch);
	pthread_mutex_unlock(&this->table->synch);
	if (this->nbr == 1)
		return (alone_routine(this), NULL);
	do_routine(this);
	pthread_mutex_unlock(&this->table->manage);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_set		set;
	t_table		_table;
	int			i;

	if (argc != 5 && argc != 6)
		return (write(2, ERR_ARG_NBR, 113), 1);
	argv++;
	if (!parsing(&set, &_table.philo, argv))
		return (write(2, ERR_ARG_RANGE, 41), 2);
	pthread_mutex_init(&_table.manage, NULL);
	i = 0;
	while (i < set.nbr)
		_table.philo[i++].table = &_table;
	if (!thread_init(&_table, &set))
		return (write(2, ERR_TH_INIT, 46), 4);
	thread_monitoring(&_table, &set);
	if (!wait_thread(&_table, &set))
		return (write(2, ERR_TH_END, 42), 5);
	ft_free(&_table, &set);
	return (0);
}
