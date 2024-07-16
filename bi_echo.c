/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:46:20 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/23 11:38:43 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_n(const char *arg)
{
	size_t	i;

	i = 0;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	bi_echo(const char **args, int fd_out)
{
	bool	flag_newline;
	size_t	i;

	flag_newline = 0;
	if (fd_out >= 0 && !args[1])
	{
		write(fd_out, "\n", 1);
		return ;
	}
	i = 1;
	while (args[i] && args[i][0] == '-' && is_only_n(&args[i][1]))
	{
		flag_newline = 1;
		i++;
	}
	while (fd_out >= 0 && args[i])
	{
		ft_putstr_fd((char *)args[i], fd_out);
		if (args[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
	if (fd_out >= 0 && flag_newline == 0)
		ft_putstr_fd("\n", fd_out);
}
