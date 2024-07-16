/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:31:03 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/11 16:10:22 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_metacharacter(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

size_t	word_len(char *line)
{
	size_t	len;
	char	quote;

	len = 0;
	quote = 0;
	while (line[len] && !((is_blank(line[len])
				|| is_metacharacter(line[len])) && quote == 0))
	{
		if (quote == 0 && (line[len] == '\'' || line[len] == '\"'))
		{
			quote = line[len];
			len++;
		}
		else if (quote == line[len])
		{
			quote = 0;
			len++;
		}
		else
			len++;
	}
	return (len);
}
