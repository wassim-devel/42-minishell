/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:16:18 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/22 11:33:14 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_ascii(char **list)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (list[i])
	{
		if (list[i + 1])
		{
			if (ft_strcmp(list[i], list[i + 1]) > 0)
			{
				temp = list[i];
				list[i] = list[i + 1];
				list[i + 1] = temp;
				i = 0;
				continue ;
			}
		}
		i++;
	}
}

void	display_sorted_env(t_envlst *envlst, int fd_out)
{
	char	**list;
	size_t	i;

	i = 0;
	list = array_convert_for_export(envlst);
	if (!list)
		return ;
	sort_ascii(list);
	while (list[i])
	{
		ft_putstr_fd(list[i], fd_out);
		ft_putstr_fd("\n", fd_out);
		i++;
	}
	free_envarray(list);
}

int	check_error_export(char *arg1)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(arg1[0]) || arg1[0] == '=')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg1, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	while (arg1[i] && arg1[i] != '=')
	{
		if (!ft_isalnum(arg1[i]) && arg1[i] != '_' && arg1[i] != '=')
		{
			ft_putstr_fd("export: ", 2);
			ft_putstr_fd(arg1, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	bi_export(char **args, t_envlst **envlst, int is_piped, int fd_out)
{
	size_t	i;
	bool	has_failed;

	i = 1;
	has_failed = 0;
	if (!args[1])
		return (display_sorted_env(*envlst, fd_out), 0);
	if (check_error_export(args[1]))
		return (1);
	if (!is_piped)
	{
		while (args[i])
		{
			if (env_set_value(envlst, args[i]) == -1)
				has_failed = 1;
			i++;
		}
		if (has_failed == 1)
			return (1);
	}
	return (0);
}
