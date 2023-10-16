/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:39:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/15 22:58:26 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	base_rout(t_philo *this)
{
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	pthread_mutex_lock(&this->table->manage);
	if (this->table->dead || &this->right_fork == this->left_fork)
		return (pthread_mutex_unlock(&this->table->manage),
			pthread_mutex_unlock(this->left_fork), false);
	pthread_mutex_unlock(&this->table->manage);
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	action(this, 1);
	ft_usleep(this, this->t_eat);
	pthread_mutex_unlock(&this->right_fork);
	pthread_mutex_unlock(this->left_fork);
	return (true);
}

bool	reverse_root(t_philo *this)
{
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	pthread_mutex_lock(&this->table->manage);
	if (this->table->dead || &this->right_fork == this->left_fork)
		return (pthread_mutex_unlock(&this->table->manage),
			pthread_mutex_unlock(&this->right_fork), false);
	pthread_mutex_unlock(&this->table->manage);
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	action(this, 1);
	ft_usleep(this, this->t_eat);
	pthread_mutex_unlock(this->left_fork);
	pthread_mutex_unlock(&this->right_fork);
	return (true);
}

bool	do_routine(t_philo *this)
{
	if (this->id % 2)
	{
		action(this, 3);
		ft_usleep(this, this->t_think);
		if (!base_rout(this))
			return (false);
	}
	else
	{
		if (!reverse_root(this))
			return (false);
		action(this, 3);
		ft_usleep(this, this->t_think);
	}
	action(this, 2);
	ft_usleep(this, this->t_sleep);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *) arg;
	pthread_mutex_lock(&this->table->manage);
	pthread_mutex_unlock(&this->table->manage);
	while (42)
		if (!do_routine(this))
			break ;
	return (NULL);
}
