/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:39:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/15 17:50:52 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	ft_usleep(t_philo *this, int time)
{
	(void)this;
	time *= 1000;
	usleep(time);
}

void	action(t_philo *this, int action)
{
	pthread_mutex_lock(&this->table->start);
	if (this->table->dead == true)
		return (pthread_mutex_unlock(&this->table->start), (void) NULL);
	if (action == 0)
		printf("%lld %i has taken a fork\n", timestamp() - this->table->t_start, this->id);
	else if (action == 1)
	{
		printf("%lld %i is eating\n", timestamp() - this->table->t_start, this->id);
		this->last_meal = timestamp();
	}
	else if (action == 2)
	{
		printf("%lld %i is sleeping\n", timestamp() - this->table->t_start, this->id);
		this->meal_nbr += 1;
	}
	else if (action == 3)
		printf("%lld %i is thinking\n", timestamp() - this->table->t_start, this->id);
	pthread_mutex_unlock(&this->table->start);
}

bool	do_routine(t_philo *this)
{
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	pthread_mutex_lock(&this->table->start);
	if (this->table->dead || &this->right_fork == this->left_fork)
		return (false);
	pthread_mutex_unlock(&this->table->start);
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	action(this, 1);
	ft_usleep(this, this->t_eat);
	pthread_mutex_unlock(this->left_fork);
	pthread_mutex_unlock(&this->right_fork);
	action(this, 2);
	ft_usleep(this, this->t_sleep);
	action(this, 3);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *) arg;
	pthread_mutex_lock(&this->table->start);
	pthread_mutex_unlock(&this->table->start);
	if (this->id % 2)
	{
		action(this, 3);
		ft_usleep(this, this->t_eat);
	}
	while (42)
		if (!do_routine(this))
			break ;
	pthread_mutex_unlock(&this->table->start);
	return (NULL);
}
