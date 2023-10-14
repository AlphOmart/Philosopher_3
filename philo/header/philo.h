/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:27:50 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 19:49:26 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>

# define ERR_ARG_NBR "\033[1;31m[ERROR]\033[1;33m Usage:<./philo> <nbr of philo> <time to die> <time to eat> <time to sleep>\
|| [nbr of meal]\n"
# define ERR_ARG_RANGE "\033[1;31m[ERROR]\033[1;33m Invalid arguments!\n"
# define ERR_TH_INIT "\033[1;31m[ERROR]\033[1;33m thread creation failed!\n"
# define ERR_TH_END "\033[1;31m[ERROR]\033[1;33m thread join failed!\n"

typedef struct s_set
{
	int	nbr;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	meal_max;
}	t_set;

typedef struct s_philo
{
	pthread_t		philo;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	int				id;
	int				nbr;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_max;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	start;
	u_int64_t		t_start;
}	t_table;

//---ft_atoll.c
int			is_white_space(char c);
long long	ft_atoll(char *nbr);

//---parsing.c
int			parsing(t_set *set, t_philo **philo, char **arg);

//---threads.c
int			thread_init(t_table *table, t_set *set);
int			wait_thread(t_table *table, t_set *set);
u_int64_t	timestamp(void);

#endif