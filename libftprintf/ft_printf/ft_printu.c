/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:29:33 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 10:11:13 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printudigits(unsigned int unb, t_format format, unsigned int base_power,
					int nbdigits)
{
	int	i;

	i = 0;
	if (unb == 0 && format.precision == 0)
		return (i);
	while (i < format.precision - nbdigits)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	while (base_power != 0)
	{
		ft_putchar_fd(unb / base_power + '0', 1);
		unb %= base_power;
		base_power /= 10;
		i++;
	}
	return (i);
}

int	ft_printuleft(unsigned int unb, t_format format)
{
	int				i;
	unsigned int	base_power;
	int				nbdigits;

	i = 0;
	base_power = 10;
	nbdigits = ft_nbdigits(unb, &base_power, format);
	i += ft_printudigits(unb, format, base_power, nbdigits);
	while (i < format.width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

int	ft_printuright(unsigned int unb, t_format format)
{
	int				i;
	unsigned int	base_power;
	int				nbspaces;
	int				nbdigits;

	base_power = 10;
	i = 0;
	if (format.precision < 0 && format.zero_flag)
		format.precision = format.width;
	nbdigits = ft_nbdigits(unb, &base_power, format);
	nbspaces = format.width - ft_maxint(format.precision, nbdigits);
	while (i < nbspaces)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	i += ft_printudigits(unb, format, base_power, nbdigits);
	return (i);
}

int	ft_printu(int unb, t_format format)
{
	if (format.minus_flag)
		return (ft_printuleft(unb, format));
	else
		return (ft_printuright(unb, format));
	return (0);
}
