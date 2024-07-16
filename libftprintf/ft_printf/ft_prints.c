/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:53:57 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 12:04:49 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printsleft(char *s, t_format format)
{
	int	i;

	i = 0;
	while (s[i] && (format.precision < 0 || i < format.precision))
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
	while (i < format.width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	return (i);
}

int	ft_printsright(char *s, t_format format, int len)
{
	int	i;
	int	j;

	i = 0;
	if (format.precision >= 0)
		len = ft_minint(len, format.precision);
	while (i < format.width - len)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	j = 0;
	while ((format.precision < 0 || j < format.precision) && s[j])
	{
		ft_putchar_fd(s[j], 1);
		j++;
	}
	return (i + j);
}

int	ft_printnull(t_format format)
{
	if (format.precision < 6 && format.precision >= 0)
	{
		if (format.minus_flag)
			return (ft_printsleft("", format));
		return (ft_printsright("", format, 0));
	}
	if (format.minus_flag)
		return (ft_printsleft("(null)", format));
	return (ft_printsright("(null)", format, 6));
}

int	ft_prints(char *s, t_format format)
{
	int	len;

	if (!s)
		return (ft_printnull(format));
	len = (int) ft_strlen(s);
	if (format.minus_flag)
		return (ft_printsleft(s, format));
	else
		return (ft_printsright(s, format, len));
}
