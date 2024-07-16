/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:12:39 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/27 13:32:06 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbdigits(unsigned int n, unsigned int *base_power, t_format format)
{
	unsigned int	nbdigits;
	unsigned int	base;

	nbdigits = 2;
	if (n == 0)
	{
		*base_power = 1;
		if (format.precision == 0)
			return (0);
	}
	if (n < *base_power)
	{
		*base_power = 1;
		return (1);
	}
	base = *base_power;
	while (*base_power <= n / base)
	{
		nbdigits++;
		*base_power *= base;
	}
	return (nbdigits);
}

int	ft_maxint(int a, int b)
{
	return ((a >= b) * a + (a < b) * b);
}

int	ft_minint(int a, int b)
{
	return ((a <= b) * a + (a > b) * b);
}
