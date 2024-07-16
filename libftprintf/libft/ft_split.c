/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:03:48 by aoizel            #+#    #+#             */
/*   Updated: 2023/12/11 15:08:54 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_strlen_char(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_strcpy_char(char *dest, const char *src, char c)
{
	unsigned int	i;

	i = 0;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

static char	**ft_write_strs(char **sout, const char *s,
							char c, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j])
		{
			sout[i] = ft_calloc((ft_strlen_char(&s[j], c) + 1), sizeof(char));
			if (!sout[i])
			{
				while (i > 0)
					free(sout[--i]);
				free (sout);
				return (NULL);
			}
			j += ft_strcpy_char(sout[i], &s[j], c);
		}
		i++;
	}
	return (sout);
}

char	**ft_split(const char *s, char c)
{
	unsigned int	size;
	char			**sout;
	unsigned int	i;

	size = 0;
	i = 0;
	while (s[i])
	{
		if (!(s[i] == c) && i == 0)
		{
			size++;
			i++;
		}
		if (!(s[i] == c) && s[i - 1] == c)
			size++;
		i++;
	}
	sout = (char **) ft_calloc((size + 1), sizeof(char *));
	if (!sout)
		return (NULL);
	sout = ft_write_strs(sout, s, c, size);
	if (!sout)
		return (NULL);
	sout[size] = NULL;
	return (sout);
}
