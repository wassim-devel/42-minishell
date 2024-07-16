/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:11:35 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/19 11:01:15 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_cd(char **args)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	update_old_pwd(t_envlst **envlst, char **curr_directory, char **oldpwd)
{
	*curr_directory = getcwd(NULL, 0);
	if (*curr_directory)
	{
		*oldpwd = ft_strjoin("OLDPWD=", *curr_directory);
		if (!*oldpwd)
		{
			free(*curr_directory);
			return (1);
		}
		free(*curr_directory);
		env_set_value(envlst, *oldpwd);
		free(*oldpwd);
	}
	return (0);
}

int	change_directory(char **args, t_envlst **envlst)
{
	if (!args[1])
	{
		if (chdir(env_get_value(*envlst, "HOME")) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	bi_cd(char **args, int is_piped, t_envlst **envlst)
{
	char	*oldpwd;
	char	*curr_directory;

	if (check_error_cd(args) == 1)
		return (1);
	if (!is_piped)
	{
		if (update_old_pwd(envlst, &curr_directory, &oldpwd) == 1)
			return (1);
		if (change_directory(args, envlst) == 1)
			return (1);
		curr_directory = getcwd(NULL, 0);
		if (!curr_directory)
			return (1);
		oldpwd = ft_strjoin("PWD=", curr_directory);
		if (!oldpwd)
			return (free(curr_directory), 1);
		free(curr_directory);
		if (env_set_value(envlst, oldpwd))
			return (1);
		free(oldpwd);
	}
	return (0);
}
