/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 14:49:08 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/22 16:06:52 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_remove_quotes(char *word)
{
	int		i;
	int		j;
	char	quote;

	quote = 0;
	i = 0;
	j = 0;
	while (word[i])
	{
		if (!quote && (word[i] == '"' || word[i] == '\''))
			quote = word[i++];
		if (quote && quote == word[i])
		{
			quote = 0;
			i++;
			continue ;
		}
		word[j] = word[i];
		i++;
		j++;
	}
	word[j] = '\0';
}

void	unescape_quotes(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '"' - 10 || word[i] == '\'' - 10)
			word[i] = word[i] + 10;
		i++;
	}
}

int	quote_removal(t_wordlst *wordlst)
{
	while (wordlst)
	{
		word_remove_quotes(wordlst->word);
		unescape_quotes(wordlst->word);
		wordlst = wordlst->next;
	}
	return (0);
}
