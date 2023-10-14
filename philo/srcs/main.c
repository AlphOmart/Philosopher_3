/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 22:02:11 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>


void	*routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *) arg;
	pthread_mutex_lock(&this->table->start);
	pthread_mutex_unlock(&this->table->start);
	while (42)
	{
		pthread_mutex_lock(&this->table->start);
		if (this->table->dead)
			break ;
		pthread_mutex_unlock(&this->table->start);
	}
	pthread_mutex_unlock(&this->table->start);
	return (NULL);
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
	if (!wait_thread(&_table, &set))
		return (write(2, ERR_TH_END, 42), 5);
	free(_table.philo);
	return (0);
}
