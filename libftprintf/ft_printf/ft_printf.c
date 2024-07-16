/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:21:43 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 14:25:34 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printformat(va_list args, t_format format)
{
	int	c;

	c = 0;
	if (format.conversion == '%' || format.conversion == '\0')
	{
		ft_putchar_fd('%', 1);
		c++;
	}
	if (format.conversion == 'c')
		c += ft_printc(va_arg(args, int), format);
	if (format.conversion == 's')
		c += ft_prints(va_arg(args, char *), format);
	if (format.conversion == 'd' || format.conversion == 'i')
		c += ft_printd(va_arg(args, int), format);
	if (format.conversion == 'u')
		c += ft_printu(va_arg(args, unsigned int), format);
	if (format.conversion == 'x')
		c += ft_printx(va_arg(args, unsigned int), format, "0123456789abcdef");
	if (format.conversion == 'X')
		c += ft_printx(va_arg(args, unsigned int), format, "0123456789ABCDEF");
	if (format.conversion == 'p')
		c += ft_printp(va_arg(args, unsigned long long), format);
	return (c);
}

int	ft_printf(const char *fstr, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	if (!fstr)
		return (-1);
	va_start(args, fstr);
	i = 0;
	count = 0;
	while (fstr[i])
	{
		if (fstr[i] != '%')
		{
			ft_putchar_fd(fstr[i], 1);
			i++;
			count++;
		}
		else
			count += ft_printformat(args, ft_getformat(&fstr[i + 1], &i));
	}
	return (count);
}
