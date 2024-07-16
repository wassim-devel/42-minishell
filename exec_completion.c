/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:29:14 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/22 11:14:52 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	job_complete(t_processlst *processlst)
{
	if (!processlst)
		return (1);
	while (processlst)
	{
		if (processlst->complete == 0)
			return (0);
		processlst = processlst->next;
	}
	return (1);
}

void	mark_status(int pid, int status, t_processlst *processlst)
{
	if (pid <= 0)
		return ;
	while (processlst->pid != pid)
		processlst = processlst->next;
	if (!processlst)
		return ;
	processlst->status = WEXITSTATUS(status);
	if (WTERMSIG(status) == SIGQUIT)
		processlst->status = 131;
	if (WTERMSIG(status) == SIGINT)
		processlst->status = 130;
	processlst->complete = 1;
}

void	wait_job_completion(t_processlst *processlst)
{
	int	pid;
	int	status;

	status = 0;
	while (!job_complete(processlst))
	{
		pid = waitpid(0, &status, WUNTRACED | WNOHANG);
		mark_status(pid, status, processlst);
	}
}
