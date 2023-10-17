/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:58:33 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/17 13:04:35 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(uint_fast64_t time)
{
	time *= 1000;
	unsigned long	elapsed_usec;
	struct timeval start, end;
	gettimeofday(&start, NULL);

	while (1)
	{
		gettimeofday(&end, NULL);
		elapsed_usec = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		if (elapsed_usec >= time)
			break;
		unsigned long remaining_usec = time - elapsed_usec;
		if (remaining_usec > 1000)
			usleep(remaining_usec / 2);
	}
}


