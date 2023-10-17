/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:39:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/17 15:34:21 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	action(t_philo *this, int action)
{
	pthread_mutex_lock(&this->table->manage);
	if (this->table->dead == true)
		return (pthread_mutex_unlock(&this->table->manage), (void) NULL);
	if (action == 0)
		printf(DEF_PROMT"%s\n", timestamp() - \
				this->table->t_start, this->id, FORK_MESS);
	else if (action == 1)
	{
		printf(DEF_PROMT"%s\n", timestamp() - \
				this->table->t_start, this->id, EATING_MESS);
	}
	else if (action == 2)
	{
		this->meal_nbr += 1;
		printf(DEF_PROMT"%s\n", timestamp() - \
				this->table->t_start, this->id, SLEEP_MESS);
	}
	else
		printf(DEF_PROMT"%s\n", timestamp() - \
				this->table->t_start, this->id, THINKING_MESS);
	pthread_mutex_unlock(&this->table->manage);
}

static void	solo_routine(t_philo *this)
{
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
}

static void	base_rout(t_philo *this)
{
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	action(this, 1);
	ft_usleep(this->t_eat - 1);
	pthread_mutex_lock(&this->table->manage);
	this->last_meal = timestamp();
	pthread_mutex_unlock(&this->table->manage);
	pthread_mutex_unlock(this->left_fork);
	pthread_mutex_unlock(&this->right_fork);
}

static void	reverse_root(t_philo *this)
{
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	action(this, 1);
	ft_usleep(this->t_eat - 1);
	pthread_mutex_lock(&this->table->manage);
	this->last_meal = timestamp();
	pthread_mutex_unlock(&this->table->manage);
	pthread_mutex_unlock(&this->right_fork);
	pthread_mutex_unlock(this->left_fork);
}

static void	do_routine(t_philo *this)
{
	if (this->id % 2 == 0)
	{
		base_rout(this);
	}
	else
		reverse_root(this);
	action(this, 2);
	ft_usleep(this->t_sleep);
	action(this, 3);
	ft_usleep(this->t_think);
}

void	*routine(void *arg)
{
	t_philo	*this;

	this = (t_philo *) arg;
	if (this->nbr == 1)
		return (solo_routine(this), NULL);
	pthread_mutex_lock(&this->table->manage);
	pthread_mutex_unlock(&this->table->manage);
	if (this->id % 2 == 0)
	{
		action(this, 3);
		ft_usleep(10);
	}
	while (42)
	{
		do_routine(this);
		pthread_mutex_lock(&this->table->manage);
		if (this->table->dead)
			break ;
		pthread_mutex_unlock(&this->table->manage);
	}
	pthread_mutex_unlock(&this->table->manage);
	return (NULL);
}
