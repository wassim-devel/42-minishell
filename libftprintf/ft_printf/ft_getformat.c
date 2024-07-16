/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getformat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:14:06 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 10:41:58 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

void	ft_initformat(t_format *format)
{
	format->minus_flag = 0;
	format->plus_flag = 0;
	format->zero_flag = 0;
	format->hash_flag = 0;
	format->space_flag = 0;
	format->width = 0;
	format->precision = -1;
	format->conversion = '\0';
}

void	ft_setflag(t_format *format, char c)
{
	if (c == '-')
		format->minus_flag = 1;
	if (c == '+')
		format->plus_flag = 1;
	if (c == '0')
		format->zero_flag = 1;
	if (c == '#')
		format->hash_flag = 1;
	if (c == ' ')
		format->space_flag = 1;
}

int	ft_getflags(const char *s, t_format *format)
{
	size_t	i;

	i = 0;
	while (ft_strchr("-+0# ", s[i]))
	{
		ft_setflag(format, s[i]);
		i++;
	}
	if (ft_isdigit(s[i]))
	{
		format->width = ft_atoi(&s[i]);
		while (ft_isdigit(s[i]))
			i++;
	}
	if (s[i] == '.')
	{
		i++;
		format->precision = ft_atoi(&s[i]);
		while (ft_strchr("+-0123456789", s[i]))
			i++;
	}
	if (ft_strchr("diuxXcsp%", s[i]))
		format->conversion = s[i];
	return (i);
}

t_format	ft_getformat(const char *s, size_t *i)
{
	size_t		offset;
	t_format	format;

	ft_initformat(&format);
	offset = ft_getflags(s, &format);
	if (format.conversion)
		*i += offset + 2;
	else
		*i += 1;
	return (format);
}
