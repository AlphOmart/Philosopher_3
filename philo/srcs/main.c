/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 18:33:58 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>


void	*routine(void *arg)
{
	t_table	*table;

	table = (t_table *) arg;
	pthread_mutex_lock(&table->start);
	printf("Coucou je suis %i \n", table->philo->id);
	pthread_mutex_unlock(&table->start);
	return (NULL);
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
	if (!thread_init(&table, &set))
		return (write(2, ERR_TH_INIT, 46), 4);
	if (!wait_thread(&table, &set))
		return (write(2, ERR_TH_END, 42), 5);
	return (0);
}
