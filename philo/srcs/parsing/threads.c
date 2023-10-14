/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:24:29 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 19:49:22 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*routine(void *arg);

u_int64_t	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000LL) + (time.tv_usec / 1000LL));
}

int	thread_init(t_table *table, t_set *set)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->start);
	while (i < set->nbr)
	{
		if (pthread_create(&table->philo[i].philo, NULL, routine, &table->philo[i]))
			return (0);
		i++;
	}
	table->t_start = timestamp();
	pthread_mutex_unlock(&table->start);
	return (1);
}

int	wait_thread(t_table *table, t_set *set)
{
	int	i;

	i = 0;
	while (i < set->nbr)
		if (pthread_join(table->philo[i++].philo, NULL))
			return (0);
	return (1);
}