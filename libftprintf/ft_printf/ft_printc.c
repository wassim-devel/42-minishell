/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:47:12 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/16 10:09:15 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

int	ft_printc(char c, t_format format)
{
	int	i;

	i = 1;
	if (format.width <= 1 || format.minus_flag)
		ft_putchar_fd(c, 1);
	while (i < format.width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (format.width > 1 && !format.minus_flag)
		ft_putchar_fd(c, 1);
	return (ft_maxint(1, format.width));
}
