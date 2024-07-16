/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_processlst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:33:29 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/23 11:19:30 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_fds(t_processlst *processlst)
{
	if (processlst->fd_in > 1)
	{
		if (dup2(processlst->fd_in, 0) == -1)
			return (perror("dup2"), -1);
		close(processlst->fd_in);
	}
	if (processlst->fd_out > 1)
	{
		if (dup2(processlst->fd_out, 1) == -1)
			return (perror("dup2"), -1);
		close(processlst->fd_out);
	}
	while (processlst)
	{
		if (processlst->fd_in > 1)
			close(processlst->fd_in);
		if (processlst->fd_out > 1)
			close(processlst->fd_out);
		processlst = processlst->next;
	}
	return (0);
}

int	exec_fork(t_processlst *processlst, char **envarray)
{
	processlst->pid = fork();
	if (processlst->pid == 0)
	{
		if (processlst->fd_in < 0 || processlst->fd_out < 0)
			exit(1);
		manage_fds(processlst);
		fork_signal_handler();
		if (!ft_strchr(processlst->argv[0], '/'))
		{
			ft_putstr_fd(processlst->argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		execve(processlst->argv[0], processlst->argv, envarray);
		perror(processlst->argv[0]);
		if (access(processlst->argv[0], F_OK) || errno == EACCES
			|| errno == E2BIG || errno == ENAMETOOLONG)
			exit(126);
		exit(127);
	}
	if (processlst->pid == -1)
		return (perror("fork"), -1);
	return (0);
}

int	exec_processlst(t_shell *shell)
{
	t_processlst	*processlst;

	processlst = shell->processlst;
	shell->envarray = env_array_convert(shell->envlst);
	if (!shell->envarray)
		return (perror("envarray"), -1);
	while (processlst)
	{
		if (processlst->builtin_index >= 0)
		{
			processlst->status = exec_builtin(processlst, shell);
			processlst->complete = 1;
		}
		else
			if (exec_fork(processlst, shell->envarray) == -1)
				return (-1);
		if (processlst->fd_in > 1)
			close(processlst->fd_in);
		if (processlst->fd_out > 1)
			close(processlst->fd_out);
		processlst = processlst->next;
	}
	wait_job_completion(shell->processlst);
	return (0);
}
