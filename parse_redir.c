/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:05:18 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/23 11:31:12 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_redir_files(t_wordlst *wordlst, t_processlst *process)
{
	int	open_flag;

	if ((wordlst->type == REDIR_OUT || wordlst->type == REDIR_APPEND))
	{
		if (process->fd_out > 1)
			close(process->fd_out);
		if (wordlst->type == REDIR_OUT)
			open_flag = O_CREAT | O_WRONLY | O_TRUNC;
		if (wordlst->type == REDIR_APPEND)
			open_flag = O_CREAT | O_WRONLY | O_APPEND;
		process->fd_out = open(wordlst->next->word, open_flag, 0644);
		if (process->fd_out < 0)
			return (perror(wordlst->next->word), 0);
	}
	if (wordlst->type == REDIR_IN)
	{
		if (process->fd_in > 1)
			close(process->fd_in);
		process->fd_in = open(wordlst->next->word, O_RDONLY);
		if (process->fd_in < 0)
			return (perror(wordlst->next->word), 0);
	}
	return (0);
}

char	*tmp_heredoc_name(void)
{
	static int	nb;
	int			basepower;
	int			tmp_nb;
	int			i;
	static char	name[26];

	i = 0;
	nb++;
	tmp_nb = nb;
	basepower = 1000000000;
	ft_bzero(name, 26);
	while (i < 15)
	{
		name[i] = "/tmp/ms_heredoc"[i];
		i++;
	}
	while (basepower)
	{
		name[i] = '0' + tmp_nb / basepower;
		tmp_nb %= basepower;
		basepower /= 10;
		i++;
	}
	return (name);
}

int	write_heredoc(t_processlst *process, char *delimiter)
{
	char	*line;

	line = NULL;
	if (heredoc_signal_handler() == -1)
		return (-1);
	while (!line || ft_strcmp(line, delimiter))
	{
		if (line)
			ft_putendl_fd(line, process->fd_in);
		free(line);
		line = readline(">");
		if (g_last_sig == SIGINT)
		{
			g_last_sig = 0;
			process->status = 130;
			return (free(line), close(process->fd_in), -1);
		}
		if (!line)
		{
			ft_putendl_fd("Warning : Heredoc ended by EOF", 2);
			break ;
		}
	}
	free(line);
	return (0);
}

int	open_heredoc(t_wordlst *wordlst, t_processlst *process)
{
	char	*heredoc_name;

	heredoc_name = tmp_heredoc_name();
	while (access(heredoc_name, F_OK) == 0)
		heredoc_name = tmp_heredoc_name();
	if (!heredoc_name)
		return (-1);
	if (process->fd_in != 0)
		close(process->fd_in);
	process->fd_in = open(heredoc_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (process->fd_in == -1)
		return (-1);
	if (write_heredoc(process, wordlst->next->word) == -1)
		return (-1);
	close(process->fd_in);
	process->fd_in = open(heredoc_name, O_RDONLY, 0644);
	if (process->fd_in == -1)
		return (-1);
	unlink(heredoc_name);
	return (0);
}

int	get_redir_files(t_wordlst *wordlst, t_processlst *process)
{
	while (wordlst && wordlst->type != PIPE)
	{
		if (wordlst->type == REDIR_OUT || wordlst->type == REDIR_IN
			|| wordlst->type == REDIR_APPEND)
		{
			if (open_redir_files(wordlst, process) == -1)
			{
				process->status = 1;
				return (-1);
			}
		}
		if (wordlst->type == REDIR_HEREDOC)
		{
			if (open_heredoc(wordlst, process) == -1)
				return (-1);
		}
		wordlst = wordlst->next;
	}
	return (0);
}
