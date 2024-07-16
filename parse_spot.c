/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:01:51 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/18 15:03:37 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	spot_operators(t_wordlst *wordlst)
{
	while (wordlst->next)
	{
		if (wordlst->type == OPERATOR && !ft_strcmp(wordlst->word, "|"))
			wordlst->type = PIPE;
		if (wordlst->type == OPERATOR && !ft_strcmp(wordlst->word, "<"))
			wordlst->type = REDIR_IN;
		if (wordlst->type == OPERATOR && !ft_strcmp(wordlst->word, ">"))
			wordlst->type = REDIR_OUT;
		if (wordlst->type == OPERATOR && !ft_strcmp(wordlst->word, ">>"))
			wordlst->type = REDIR_APPEND;
		if (wordlst->type == OPERATOR && !ft_strcmp(wordlst->word, "<<"))
			wordlst->type = REDIR_HEREDOC;
		if (wordlst->type == REDIR_IN || wordlst->type == REDIR_OUT
			|| wordlst->type == REDIR_APPEND)
			wordlst->next->type = REDIR_FILE;
		if (wordlst->type == REDIR_HEREDOC)
			wordlst->next->type = DELIMITER;
		wordlst = wordlst->next;
	}
}

int	spot_builtin(t_wordlst *wordlst, t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->builtins[i])
	{
		if (!ft_strcmp(wordlst->word, shell->builtins[i]))
		{
			wordlst->type = BUILTIN + i;
			return (0);
		}
		i++;
	}
	return (-1);
}

void	spot_words(t_shell *shell)
{
	int			first;
	t_wordlst	*wordlst;

	first = 1;
	wordlst = shell->wordlst;
	while (wordlst)
	{
		if (wordlst->type == WORD && first == 1)
		{
			if (spot_builtin(wordlst, shell) == -1)
				wordlst->type = CMD;
			first = 0;
		}
		else if (wordlst->type == WORD)
			wordlst->type = ARG;
		if (wordlst->type == PIPE)
			first = 1;
		wordlst = wordlst->next;
	}
}
