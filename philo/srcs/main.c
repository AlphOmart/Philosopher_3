/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/15 16:13:56 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	checker(t_table	*table, t_set *set)
{
	t_philo		*philo;
	u_int64_t	time;
	int			meal_count;
	int		i;

	i = 0;
	time = timestamp();
	(void)meal_count;
	(void)table;
	(void)time;
	(void)set;
	(void)philo;
	while (i < set->nbr)
	{
		philo = &table->philo[i];
		if (table->philo->t_die < time - philo->last_meal)
			return (printf("%lld %i died\n", timestamp() - table->t_start, philo->id), 0);
		i++;
	}
	return (1);
}

void	thread_monitoring(t_table *table, t_set *set)
{
	while (42)
	{
		pthread_mutex_lock(&table->start);
		if (!checker(table, set))
		{
			table->dead = true;
			pthread_mutex_unlock(&table->start);
			break ;
		}
		pthread_mutex_unlock(&table->start);
	}
}

//TODO simplifier philo  et table.philo en une seul struct table.philo
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
	pthread_mutex_init(&_table.start, NULL);
	i = 0;
	while (i < set.nbr)
		_table.philo[i++].table = &_table;
	if (!thread_init(&_table, &set))
		return (write(2, ERR_TH_INIT, 46), 4);
	thread_monitoring(&_table, &set);
	if (!wait_thread(&_table, &set))
		return (write(2, ERR_TH_END, 42), 5);
	free(_table.philo);
	return (0);
}
