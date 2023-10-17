/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:27:50 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/17 13:01:25 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>

# define ERR_ARG_NBR "\033[1;31m[ERROR]\033[1;33m Usage:<./philo> <nbr of philo> <time to die> <time to eat> <time to sleep>\
|| [nbr of meal]\n"
# define ERR_ARG_RANGE "\033[1;31m[ERROR]\033[1;33m Invalid arguments!\n"
# define ERR_TH_INIT "\033[1;31m[ERROR]\033[1;33m thread creation failed!\n"
# define ERR_TH_END "\033[1;31m[ERROR]\033[1;33m thread join failed!\n"

# define DEF_PROMT "%lld %i "
# define FORK_MESS "has taken a fork"
# define EATING_MESS "is eating"
# define SLEEP_MESS "is sleeping"
# define THINKING_MESS "is thinking"
# define DIED_MESS "died"

typedef struct s_set
{
	int 	nbr;
	int_fast64_t		t_die;
	int_fast64_t		t_eat;
	int_fast64_t	t_sleep;
	int_fast64_t	meal_max;
}	t_set;

typedef struct s_philo
{
	pthread_t			philo;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	int					id;
	int					nbr;
	int_fast64_t		t_die;
	int_fast64_t		t_eat;
	int_fast64_t		t_sleep;
	int_fast64_t		t_think;
	int					meal_nbr;
	uint_fast64_t		last_meal;
	struct s_table		*table;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	manage;
	bool			dead;
	uint_fast64_t		t_start;
}	t_table;

//---ft_atoll.c
int			is_white_space(char c);
long long	ft_atoll(char *nbr);

//---parsing.c
int			parsing(t_set *set, t_philo **philo, char **arg);

//---threads.c
int			thread_init(t_table *table, t_set *set);
int			wait_thread(t_table *table, t_set *set);
uint_fast64_t	timestamp(void);

//---routine.c
void		*routine(void *arg);

//---action.c
void		ft_usleep(uint_fast64_t time);
#endif
