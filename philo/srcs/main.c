/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 15:38:57 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#define ERR_TH_INIT "[ERROR] thread creation failed !"

#include <stdio.h>

typedef struct s_table
{
	t_philo			*philo;
	pthread_mutex_t	start;
	int				i;
}	t_table;


//TODO simplifier philo  et table.philo en une seul struct table.philo
int	main(int argc, char **argv)
{
	t_set		set;
	t_philo		*philo;
	t_table		table;

	philo = NULL;
	if (argc != 5 && argc != 6)
		return (write(2, ERR_ARG_NBR, 113), 1);
	argv++;
	if (!parsing(&set, &philo, argv))
		return (write(2, ERR_ARG_RANGE, 41), 2);
	table.philo = philo;
	return (0);
}