/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:34:30 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/09 10:40:54 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	charc;

	i = 0;
	charc = (char) c;
	if (!ft_isascii(charc))
		return ((char *)s);
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == charc)
			return ((char *)s + i);
		i--;
	}
	if (s[i] == charc)
		return ((char *)s + i);
	return (NULL);
}
