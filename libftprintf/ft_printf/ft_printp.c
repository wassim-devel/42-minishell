/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:30:59 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 17:24:30 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_nbdigitsp(unsigned long long n, unsigned long long *base_power,
				t_format format)
{
	unsigned int		nbdigits;
	unsigned long long	base;

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

int	ft_printpdigits(unsigned long long unb, t_format format,
					const char *hex_base)
{
	int					i;
	unsigned long long	base_power;
	int					nbdigits;

	i = 0;
	base_power = 16;
	nbdigits = ft_nbdigitsp(unb, &base_power, format);
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

int	ft_printpleft(unsigned long long unb, t_format format)
{
	int					i;
	unsigned long long	base_power;

	i = 0;
	base_power = 16;
	ft_nbdigitsp(unb, &base_power, format);
	ft_putstr_fd("0x", 1);
	i += 2;
	i += ft_printpdigits(unb, format, "0123456789abcdef");
	while (i < format.width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

int	ft_printpright(unsigned long long unb, t_format format)
{
	int					i;
	unsigned long long	base_power;
	int					nbspaces;
	int					nbdigits;

	base_power = 16;
	i = 0;
	nbdigits = ft_nbdigitsp(unb, &base_power, format);
	nbspaces = format.width - ft_maxint(nbdigits, format.precision) - 2;
	while (i < nbspaces)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putstr_fd("0x", 1);
	i += 2;
	i += ft_printpdigits(unb, format, "0123456789abcdef");
	return (i);
}

int	ft_printp(unsigned long long unb, t_format format)
{
	if (unb == 0)
	{
		format.precision = -1;
		return (ft_prints("(nil)", format));
	}
	if (format.minus_flag)
		return (ft_printpleft(unb, format));
	else
		return (ft_printpright(unb, format));
	return (0);
}
