/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:22:29 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/07 13:49:17 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;
	size_t	total_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	total_len = dest_len + src_len;
	if (size == 0)
		return (src_len);
	if (dest_len >= size)
		return (size + src_len);
	size -= dest_len;
	i = dest_len;
	j = 0;
	while (src[j] && size > 1)
	{
		dest[i] = src[j];
		i++;
		j++;
		size--;
	}
	dest[i] = '\0';
	return (total_len);
}
