/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 11:16:45 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/22 15:54:09 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*joinstr_with_slash(const char *str1, const char *str2)
{
	size_t	i;
	size_t	j;
	char	*to_return;

	i = 0;
	j = 0;
	to_return = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 2));
	if (!to_return)
		return (NULL);
	while (str1[i])
	{
		to_return[i] = str1[i];
		i++;
	}
	to_return[i++] = '/';
	while (str2[j])
	{
		to_return[i] = str2[j];
		i++;
		j++;
	}
	to_return[i] = '\0';
	return (to_return);
}

void	free_ft_split(char **splited_path)
{
	size_t	i;

	i = 0;
	while (splited_path[i])
	{
		free(splited_path[i]);
		i++;
	}
	free(splited_path);
}

char	*retrieve_absolute_path(t_envlst *envlst, const char *executable)
{
	char	**splited_path;
	char	*joined_str;
	ssize_t	i;

	if (env_get_value(envlst, "PATH"))
		splited_path = ft_split(env_get_value(envlst, "PATH"), ':');
	if (!env_get_value(envlst, "PATH") || !splited_path || !executable[0])
		return (ft_strdup(executable));
	i = -1;
	while (splited_path[++i])
	{
		joined_str = joinstr_with_slash(splited_path[i], executable);
		if (access(joined_str, F_OK) == 0)
			return (free_ft_split(splited_path), joined_str);
		free(joined_str);
	}
	free_ft_split(splited_path);
	i = -1;
	joined_str = malloc(sizeof(char) * (ft_strlen(executable) + 1));
	if (!joined_str)
		return (ft_strdup(executable));
	while (executable[++i])
		joined_str[i] = executable[i];
	joined_str[i] = '\0';
	return (joined_str);
}
