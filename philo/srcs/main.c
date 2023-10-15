/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/15 12:15:07 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	ft_usleep(t_philo *this, int time)
{
	(void)this;
	time *= 1000;
	usleep(time);
}

void	*routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *) arg;
	pthread_mutex_lock(&this->table->start);
	pthread_mutex_unlock(&this->table->start);
	if (this->id % 2)
	{
		printf("%lld %i is thinking\n", timestamp() - this->table->t_start, this->id);
		ft_usleep(this, this->t_eat);
	}
	while (42)
	{
		pthread_mutex_lock(&this->table->start);
		if (this->table->dead)
			break ;
		pthread_mutex_unlock(&this->table->start);
		pthread_mutex_lock(this->left_fork);
		printf("%lld %i has taken left fork\n", timestamp() - this->table->t_start, this->id);
		pthread_mutex_lock(&this->right_fork);
		printf("%lld %i has taken right fork\n", timestamp() - this->table->t_start, this->id);
		printf("%lld %i is eating\n", timestamp() - this->table->t_start, this->id);
		this->last_meal = timestamp();
		ft_usleep(this, this->t_eat);
		pthread_mutex_unlock(this->left_fork);
		pthread_mutex_unlock(&this->right_fork);
		printf("%lld %i is sleeping\n", timestamp() - this->table->t_start, this->id);
		ft_usleep(this, this->t_sleep);
		printf("%lld %i is thinking\n", timestamp() - this->table->t_start, this->id);
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
