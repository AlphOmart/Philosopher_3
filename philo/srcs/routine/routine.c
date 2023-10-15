/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:39:18 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/15 19:52:45 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	print_message(t_philo *this, int mess)
{
	if (mess != 5)
		printf(DEF_PROMT, timestamp() - this->table->t_start, this->id);
	if (mess == 0)
		printf("%-36s|\n", FORK_MESS);
	else if (mess == 1)
		printf("%-36s|\n", EATING_MESS);
	else if (mess == 2)
		printf("%-36s|\n", SLEEP_MESS);
	else if (mess == 3)
		printf("%-36s|\n", THINKING_MESS);
	else if (mess == 4)
		printf("%-38s|\n", DIED_MESS);
	else if (mess == 5)
	{
		printf(LINE_SPACING);
		printf(PROMPT_MENU);
	}
	printf(LINE_SPACING);
}

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
		print_message(this, action);
	else if (action == 1)
	{
		print_message(this, action);
		this->last_meal = timestamp();
	}
	else if (action == 2)
	{
		print_message(this, action);
		this->meal_nbr += 1;
	}
	else if (action == 3)
		print_message(this, 3);
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
