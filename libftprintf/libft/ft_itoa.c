/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:30:11 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/09 12:06:38 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itos(unsigned int nb, unsigned int base_power,
					unsigned int size, int sign)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (sign == -1)
	{
		str[i] = '-';
		i++;
	}
	while (base_power != 0)
	{
		str[i] = nb / base_power + 48;
		nb %= base_power;
		base_power /= 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nb;
	unsigned int	base_power;
	unsigned int	size;
	int				sign;
	char			*str;	

	base_power = 1;
	size = 1;
	sign = 1;
	if (n < 0)
	{
		size++;
		sign = -1;
		nb = (unsigned int) -n;
	}
	else
		nb = n;
	while (base_power <= nb / 10 && nb != 0)
	{
		base_power *= 10;
		size++;
	}
	str = ft_itos(nb, base_power, size, sign);
	return (str);
}
