/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:21:22 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/27 13:45:23 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../libft/libft.h"

typedef struct s_format
{
	int		width;
	int		precision;
	char	conversion;
	int		minus_flag;
	int		plus_flag;
	int		zero_flag;
	int		hash_flag;
	int		space_flag;
}				t_format;

int			ft_printf(const char *fstr, ...);
int			ft_printc(char c, t_format format);
int			ft_prints(char *s, t_format format);
int			ft_printd(int nb, t_format format);
int			ft_printu(int unb, t_format format);
int			ft_printx(int unb, t_format format, const char *hex_base);
int			ft_printp(unsigned long long unb, t_format format);
t_format	ft_getformat(const char *s, size_t *i);
int			ft_nbdigits(unsigned int n, unsigned int *base_power,
				t_format format);
int			ft_maxint(int a, int b);
int			ft_minint(int a, int b);
#endif
