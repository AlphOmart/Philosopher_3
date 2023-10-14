/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:24:29 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 18:50:14 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg);

int	thread_init(t_table *table, t_set *set)
{
	int	i;

	i = 0;
	while (i < set->nbr)
	{
		pthread_mutex_lock(&table->start);
		if (pthread_create(&table->philo[i].philo, NULL, routine, &table->philo[i]))
			return (0);
		i++;
	}
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