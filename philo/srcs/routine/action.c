#include "philo.h"

void	print_message(t_philo *this, int mess)
{
	if (mess != 5)
		printf(DEF_PROMT, timestamp() - this->table->t_start, this->id);
	if (mess == 0)
		printf("%s\n", FORK_MESS);
	else if (mess == 1)
		printf("%s\n", EATING_MESS);
	else if (mess == 2)
		printf("%s\n", SLEEP_MESS);
	else if (mess == 3)
		printf("%s\n", THINKING_MESS);
	else if (mess == 4)
		printf("%s\n", DIED_MESS);
}

void	ft_usleep(t_philo *this, unsigned long long time)
{
	(void)this;
	time *= 1000;
	usleep(time);
}

void	action(t_philo *this, int action)
{
	pthread_mutex_lock(&this->table->manage);
	if (this->table->dead == true)
		return (pthread_mutex_unlock(&this->table->manage), (void) NULL);
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
	pthread_mutex_unlock(&this->table->manage);
}
