/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 16:03:46 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#define ERR_TH_INIT "[ERROR] thread creation failed !"

#include <stdio.h>



void	*routine(void *arg)
{
	t_table	*table;
	int		i;
	table = (t_table *) arg;

	pthread_mutex_lock(&table->start);
	i = 0;
	while (i < table->philo[i].nbr)
	{
		printf("%i ", table->philo[i].id);
		printf("%i ", table->philo[i].nbr);
		printf("%i ", table->philo[i].t_die);
		printf("%i ", table->philo[i].t_eat);
		printf("%i ", table->philo[i].t_sleep);
		printf("%i\n", table->philo[i].meal_max);
		i++;
	}
	pthread_mutex_unlock(&table->start);
	return (NULL);
}

int	thread_init(t_table *table, t_set *set)
{
	int	i;

	i = 0;
	while (i < set->nbr)
	{
		if (pthread_create(&table->philo[i].philo, NULL, routine, table) != 0)
			return (0);
		i++;
	}
	return (1);
}

//TODO simplifier philo  et table.philo en une seul struct table.philo
int	main(int argc, char **argv)
{
	t_set		set;
	t_philo		*philo;
	t_table		table;

	philo = NULL;
	if (argc != 5 && argc != 6)
		return (write(2, ERR_ARG_NBR, 113), 1);
	argv++;
	if (!parsing(&set, &philo, argv))
		return (write(2, ERR_ARG_RANGE, 41), 2);
	table.philo = philo;
	pthread_mutex_init(&table.start, NULL);
	thread_init(&table, &set);
	int i = 0;
	while(i < set.nbr)
	{
		pthread_join(table.philo[i].philo, NULL);
		i++;
	}
	return (0);
}