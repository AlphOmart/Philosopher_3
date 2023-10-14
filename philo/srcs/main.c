/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:03:54 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 12:40:04 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_set	set;


	(void)argv;
	if (argc != 5 && argc != 6)
		return (write(2, ERR_ARG_NBR, 113), 1);
	argv++;
	if (!parsing(&set, argv))
		return (write(2, ERR_ARG_RANGE, 41), 2);
	printf("nombre de philo = %i\n", set.nbr);
	printf("time to die = %i\n", set.t_die);
	printf("time to eat = %i\n", set.t_eat);
	printf("t_sleep = %i\n", set.t_sleep);
	printf("eat_nbr = %i\n", set.eat_nbr);
	return (0);
}