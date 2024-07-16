/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:10:09 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/19 10:58:58 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	connect_pipe(t_processlst *process_lst, t_processlst *new_process)
{
	int	pipe_fd[2];

	if (!process_lst)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	while (process_lst->next)
		process_lst = process_lst->next;
	if (process_lst->fd_out == 1)
		process_lst->fd_out = pipe_fd[1];
	else
		close(pipe_fd[1]);
	new_process->fd_in = pipe_fd[0];
	process_lst->is_piped = 1;
	new_process->is_piped = 1;
	return (0);
}
