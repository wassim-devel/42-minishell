/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:45:25 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 11:50:42 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_letter_before(const char *command_line, ssize_t i, bool is_pipe)
{
	i -= 1;
	if (i == 0)
	{
		if (is_metacharacter(command_line[i]))
			return (1);
		return (0);
	}
	while (i > 0)
	{
		while (is_blank(command_line[i]))
			i--;
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

bool	check_only_blanks(const char *command_line)
{
	int	i;

	i = 0;
	while (is_blank(command_line[i]))
		i++;
	if (!command_line[i])
		return (1);
	return (0);
}
