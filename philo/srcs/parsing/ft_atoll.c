/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwubneh <mwubneh@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:26:43 by mwubneh           #+#    #+#             */
/*   Updated: 2023/10/14 12:26:57 by mwubneh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_white_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' )
		return (1);
	else if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	is_sign(char c, int *sign)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		return (1);
	}
	return (0);
}

long long	ft_atoll(char *nbr)
{
	long long	res;
	long long	tmp;
	int			sign;

	sign = 1;
	while (is_white_space(*nbr))
		nbr++;
	if (is_sign(*nbr, &sign))
		nbr++;
	res = 0;
	while ('0' <= *nbr && *nbr <= '9')
	{
		tmp = res * 10 + (*nbr++ - '0');
		if (tmp < res)
		{
			if (sign < 0)
				return (LLONG_MIN);
			return (LLONG_MAX);
		}
		res = tmp;
	}
	if (sign < 0)
		return (sign * res);
	return (res);
}
