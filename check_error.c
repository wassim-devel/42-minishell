/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:17:56 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/23 12:55:46 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_letter_after(const char *command_line, ssize_t i, bool is_pipe)
{
	i += 1;
	while (command_line[i])
	{
		while (is_blank(command_line[i]))
			i++;
		if (!command_line[i])
			return (1);
		if (is_pipe)
		{
			if (command_line[i] == '|')
				return (1);
		}
		else if (!is_pipe)
		{
			if (is_metacharacter(command_line[i]))
				return (1);
		}
		return (0);
	}
	return (1);
}

bool	check_letter_before_and_after(const char *command_line, ssize_t i,
			bool is_pipe)
{
	if (check_letter_before(command_line, i, is_pipe)
		|| check_letter_after(command_line, i, is_pipe))
		return (1);
	return (0);
}

bool	invalid_operator(const char c, const char *command_line, ssize_t i)
{
	if ((c == '<' && command_line[i + 1] != '<')
		|| (c == '>' && command_line[i + 1] != '>'))
	{
		if (check_letter_after(command_line, i, 0))
		{
			return (1);
		}
	}
	if ((c == '<' || c == '>') && command_line[i + 1] == c
		&& command_line[i + 2] == c)
		return (1);
	else if (c == '|')
	{
		if (check_letter_before_and_after(command_line, i, 1))
		{
			return (1);
		}
	}
	return (0);
}

bool	check_quotes(const char *command_line)
{
	size_t	i;
	bool	flag;
	bool	flag_simple;

	i = 0;
	flag = 0;
	flag_simple = 0;
	while (command_line[i])
	{
		if (command_line[i] == '"' && flag == 0 && flag_simple != 1)
			flag = 1;
		else if (command_line[i] == '"' && flag == 1 && flag_simple != 1)
			flag = 0;
		else if (command_line[i] == '\'' && flag_simple == 0 && flag != 1)
			flag_simple = 1;
		else if (command_line[i] == '\'' && flag_simple == 1 && flag != 1)
			flag_simple = 0;
		i++;
	}
	if (flag == 1 || flag_simple == 1)
		return (1);
	return (0);
}

bool	check_error(const char *command_line)
{
	ssize_t	i;
	char	quote;

	i = 0;
	quote = 0;
	if (check_only_blanks(command_line))
		return (1);
	if (check_quotes(command_line))
		return (write(2, "minishell : syntax error\n", 25) - 24);
	while (command_line[i])
	{
		if (!quote && (command_line[i] == '\'' || command_line[i] == '"'))
		{
			quote = command_line[i];
			i++;
		}
		if (quote && command_line[i] == quote)
			quote = 0;
		if (!quote && invalid_operator(command_line[i], command_line, i))
			return (write(2, "minishell : syntax error\n", 25) - 24);
		i++;
	}
	return (0);
}
