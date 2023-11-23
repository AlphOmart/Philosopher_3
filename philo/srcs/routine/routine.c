/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:39:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/11/23 15:58:44 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	action(t_philo *this, int action)
{
	pthread_mutex_lock(&this->table->manage);
	if (this->table->dead == true)
		return (pthread_mutex_unlock(&this->table->manage), (void) NULL);
	if (action == 0)
		return (printf(DEF_PROMT"%s\n", timestamp() - \
			this->table->t_start, this->id, FORK_MESS),
			pthread_mutex_unlock(&this->table->manage), (void) NULL);
	else if (action == 1)
	{
		this->last_meal = timestamp();
		return (printf(DEF_PROMT"%s\n", timestamp() - \
			this->table->t_start, this->id, EATING_MESS),
			pthread_mutex_unlock(&this->table->manage), (void) NULL);
	}
	else if (action == 2)
	{
		this->meal_nbr += 1;
		return (printf(DEF_PROMT"%s\n", timestamp() - \
			this->table->t_start, this->id, SLEEP_MESS),
			pthread_mutex_unlock(&this->table->manage), (void) NULL);
	}
	else
		return (printf(DEF_PROMT"%s\n", timestamp() - \
			this->table->t_start, this->id, THINKING_MESS),
			pthread_mutex_unlock(&this->table->manage), (void) NULL);
}

static void	base_rout(t_philo *this)
{
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	action(this, 1);
	ft_usleep(this->t_eat);
	pthread_mutex_unlock(&this->right_fork);
	pthread_mutex_unlock(this->left_fork);
	action(this, 2);
	ft_usleep(this->t_sleep);
	action(this, 3);
	ft_usleep(this->t_think);
}

static void	reverse_root(t_philo *this)
{
	pthread_mutex_lock(&this->right_fork);
	action(this, 0);
	this->r_fork = true;
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	*(this->l_fork) = true;
	action(this, 1);
	ft_usleep(this->t_eat);
	*(this->l_fork) = false;
	pthread_mutex_unlock(this->left_fork);
	this->r_fork = false;
	pthread_mutex_unlock(&this->right_fork);
	action(this, 2);
	ft_usleep(this->t_sleep);
	action(this, 3);
	ft_usleep(this->t_think);
}

void	solo_routine(t_philo *this)
{
	pthread_mutex_lock(this->left_fork);
	action(this, 0);
	pthread_mutex_unlock(this->left_fork);
}

void	do_routine(t_philo *this)
{
	if (this->id % 2 == 0)
	{
		action(this, 3);
		ft_usleep(5);
		while (42)
		{
			base_rout(this);
			pthread_mutex_lock(&this->table->manage);
			if (this->table->dead)
				break ;
			pthread_mutex_unlock(&this->table->manage);
		}
	}
	else
	{
		while (42)
		{
			reverse_root(this);
			pthread_mutex_lock(&this->table->manage);
			if (this->table->dead)
				break ;
			pthread_mutex_unlock(&this->table->manage);
		}
	}
}
