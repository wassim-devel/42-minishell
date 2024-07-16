/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:20:03 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 10:55:49 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printdzeros(unsigned int unb, t_format format)
{
	unsigned int	base_power;
	int				i;
	int				nbdigits;

	i = 0;
	base_power = 10;
	nbdigits = ft_nbdigits(unb, &base_power, format);
	while (i < format.precision - nbdigits)
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	return (i);
}

int	ft_printdigits(unsigned int unb, int sign, t_format format,
					unsigned int base_power)
{
	int	i;

	i = 0;
	if (format.plus_flag || format.space_flag || sign < 0)
	{
		if (format.plus_flag && sign > 0)
			ft_putchar_fd('+', 1);
		else if (format.space_flag && sign > 0)
			ft_putchar_fd(' ', 1);
		if (sign < 0)
			ft_putchar_fd('-', 1);
		i++;
	}
	if (unb == 0 && format.precision == 0)
		return (i);
	i += ft_printdzeros(unb, format);
	while (base_power != 0)
	{
		ft_putchar_fd(unb / base_power + '0', 1);
		unb %= base_power;
		base_power /= 10;
		i++;
	}
	return (i);
}

int	ft_printdleft(unsigned int unb, t_format format, int sign)
{
	int				i;
	unsigned int	base_power;

	i = 0;
	base_power = 10;
	ft_nbdigits(unb, &base_power, format);
	i += ft_printdigits(unb, sign, format, base_power);
	while (i < format.width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

int	ft_printdright(unsigned int unb, t_format format, int sign)
{
	int				i;
	unsigned int	base_power;
	int				nbspaces;
	int				nbdigits;

	base_power = 10;
	i = 0;
	if (format.precision < 0 && format.zero_flag)
	{
		format.precision = format.width
			- (sign == -1 || format.space_flag || format.plus_flag);
	}
	nbdigits = ft_nbdigits(unb, &base_power, format);
	nbspaces = format.width - ft_maxint(format.precision, nbdigits);
	if (sign < 0 || format.plus_flag || format.space_flag)
		nbspaces--;
	while (i < nbspaces)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	i += ft_printdigits(unb, sign, format, base_power);
	return (i);
}

int	ft_printd(int nb, t_format format)
{
	unsigned int	unb;
	int				sign;

	sign = 1;
	if (nb < 0)
	{
		sign = -1;
		unb = (unsigned int) -nb;
	}
	else
		unb = (unsigned int) nb;
	if (format.minus_flag)
		return (ft_printdleft(unb, format, sign));
	else
		return (ft_printdright(unb, format, sign));
	return (0);
}
