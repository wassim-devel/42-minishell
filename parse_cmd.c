/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:39:25 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/19 09:17:04 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_process_lst(t_processlst **processlst, t_processlst *new_process)
{
	t_processlst	*last_process;

	last_process = *processlst;
	if (!last_process)
	{
		*processlst = new_process;
		return ;
	}
	while (last_process->next)
		last_process = last_process->next;
	last_process->next = new_process;
}

int	build_process_lst(t_wordlst *wordlst, t_processlst **process_lst,
					t_shell *shell)
{
	t_processlst	*new_process;

	while (wordlst)
	{
		new_process = ft_calloc(1, sizeof(t_processlst));
		if (!new_process)
			return (-1);
		new_process->fd_out = 1;
		if (wordlst->type == PIPE)
		{
			if (connect_pipe(*process_lst, new_process))
				return (free(new_process), -1);
			wordlst = wordlst->next;
		}
		if (get_args(wordlst, new_process, shell) == -1)
			return (free(new_process), -1);
		if (get_redir_files(wordlst, new_process) == -1)
			return (add_to_process_lst(process_lst, new_process), -1);
		add_to_process_lst(process_lst, new_process);
		while (wordlst && wordlst->type != PIPE)
			wordlst = wordlst->next;
	}
	return (0);
}

int	parse_cmd(t_shell *shell)
{
	spot_operators(shell->wordlst);
	spot_words(shell);
	if (build_process_lst(shell->wordlst, &shell->processlst, shell) == -1)
		return (-1);
	return (0);
}
