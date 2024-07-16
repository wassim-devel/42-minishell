/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:01:46 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/22 15:34:51 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printxdigits(unsigned int unb, t_format format, const char *hex_base)
{
	int				i;
	int				nbdigits;
	unsigned int	base_power;

	i = 0;
	base_power = 16;
	nbdigits = ft_nbdigits(unb, &base_power, format);
	if (unb == 0 && format.precision == 0)
		return (i);
	while (i < format.precision - nbdigits)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	while (base_power != 0)
	{
		ft_putchar_fd(hex_base[unb / base_power], 1);
		unb %= base_power;
		base_power /= 16;
		i++;
	}
	return (i);
}

int	ft_printxleft(unsigned int unb, t_format format, const char *hex_base)
{
	int				i;
	unsigned int	base_power;

	i = 0;
	base_power = 16;
	ft_nbdigits(unb, &base_power, format);
	if (format.hash_flag && unb != 0)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd(format.conversion, 1);
		i += 2;
	}
	i += ft_printxdigits(unb, format, hex_base);
	while (i < format.width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

int	ft_printxright(unsigned int unb, t_format format, const char *hex_base)
{
	int				i;
	unsigned int	base_power;
	int				nbspaces;
	int				nbdigits;

	base_power = 16;
	i = 0;
	if (format.precision < 0 && format.zero_flag)
		format.precision = format.width;
	nbdigits = ft_nbdigits(unb, &base_power, format);
	nbspaces = format.width - ft_maxint(format.precision, nbdigits)
		- 2 * (format.hash_flag * unb != 0);
	while (i < nbspaces)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (format.hash_flag && unb != 0)
	{
		ft_putchar_fd('0', 1);
		ft_putchar_fd(format.conversion, 1);
		i += 2;
	}
	i += ft_printxdigits(unb, format, hex_base);
	return (i);
}

int	ft_printx(int unb, t_format format, const char *hex_base)
{
	if (format.minus_flag)
		return (ft_printxleft(unb, format, hex_base));
	else
		return (ft_printxright(unb, format, hex_base));
	return (0);
}
