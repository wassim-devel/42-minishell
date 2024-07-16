/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:29 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/22 12:15:13 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char **line)
{
	char	*word;
	size_t	i;
	size_t	len;

	len = word_len(*line);
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (**line && i < len)
	{
		word[i] = **line;
		i++;
		(*line)++;
	}
	word[len] = '\0';
	return (word);
}

int	add_word(char **line, t_wordlst **word_list)
{
	t_wordlst	*word_elem;
	t_wordlst	*last_word;

	word_elem = ft_calloc(1, sizeof(t_wordlst));
	if (!word_elem)
		return (-1);
	word_elem->word = get_word(line);
	if (!word_elem->word)
		return (free(word_elem), -1);
	word_elem->type = WORD;
	last_word = *word_list;
	if (!last_word)
	{
		*word_list = word_elem;
		return (0);
	}
	while (last_word->next)
		last_word = last_word->next;
	last_word->next = word_elem;
	return (0);
}

char	*get_operator(char **line)
{
	char	*word;
	size_t	i;
	size_t	len;

	len = 1;
	if (**line == *(*line + 1))
		len = 2;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (**line && i < len)
	{
		word[i] = **line;
		i++;
		(*line)++;
	}
	word[len] = '\0';
	return (word);
}

int	add_operator(char **line, t_wordlst **word_list)
{
	t_wordlst	*word_elem;
	t_wordlst	*last_word;

	word_elem = ft_calloc(1, sizeof(t_wordlst));
	if (!word_elem)
		return (-1);
	word_elem->word = get_operator(line);
	if (!word_elem->word)
		return (free(word_elem), -1);
	word_elem->type = OPERATOR;
	last_word = *word_list;
	if (!last_word)
	{
		*word_list = word_elem;
		return (0);
	}
	while (last_word->next)
		last_word = last_word->next;
	last_word->next = word_elem;
	return (0);
}

int	parse_words(char *line, t_wordlst **word_list)
{
	while (*line)
	{
		while (is_blank(*line))
			line++;
		if (is_metacharacter(*line))
		{
			if (add_operator(&line, word_list) == -1)
				return (perror("minishell"), -1);
		}
		else if (*line)
		{
			if (add_word(&line, word_list) == -1)
				return (perror("minishell"), -1);
		}
	}
	return (0);
}
