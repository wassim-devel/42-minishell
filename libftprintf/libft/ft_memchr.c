/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:00:54 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/09 10:51:08 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*mem;
	char	charc;

	mem = (char *) s;
	i = 0;
	charc = (char) c;
	while (i < n)
	{
		if (mem[i] == charc)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
