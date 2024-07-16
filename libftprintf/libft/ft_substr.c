/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:35:27 by aoizel            #+#    #+#             */
/*   Updated: 2023/11/09 12:11:27 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	size_needed;

	i = 0;
	if (start >= ft_strlen(s))
		size_needed = 0;
	else if (start + len > ft_strlen(s))
		size_needed = ft_strlen(s) - start;
	else
		size_needed = len;
	sub = malloc((size_needed + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	while (i < size_needed && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
