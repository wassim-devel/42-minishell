/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:30:16 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/09 10:37:56 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			charc;

	i = 0;
	charc = (char) c;
	if (!ft_isascii(charc))
		return ((char *)s);
	while (s[i])
	{
		if ((unsigned char) s[i] == charc)
			return ((char *) s + i);
		i++;
	}
	if ((unsigned char) s[i] == charc)
		return ((char *) s + i);
	return (NULL);
}
