/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:27:50 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 12:37:50 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <limits.h>
# include <pthread.h>

# define ERR_ARG_NBR "\033[1;31m[ERROR]\033[1;33m Usage:<./philo> <nbr of philo> <time to eat> <time to sleep> <time to die>\
|| <nbr of meal>\n"
# define ERR_ARG_RANGE "\033[1;31m[ERROR]\033[1;33m Invalid arguments\n"

typedef struct s_set
{
	int	nbr;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	eat_nbr;
}	t_set;


//---ft_atoll.c
int			is_white_space(char c);
long long	ft_atoll(char *nbr);

//---parsing.c
int			parsing(t_set *set, char **arg);

#endif