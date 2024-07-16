/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array_convert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:57:30 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/11 16:09:58 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_array_keyvalue(char *to_return, t_envlst *env_list)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (env_list->key[j])
	{
		to_return[k] = env_list->key[j];
		k++;
		j++;
	}
	to_return[k++] = '=';
	j = 0;
	while (env_list->value[j])
	{
		to_return[k] = env_list->value[j];
		k++;
		j++;
	}
	to_return[k] = '\0';
}

char	**env_array_convert(t_envlst *env_list)
{
	char	**to_return;
	ssize_t	i;

	to_return = malloc(sizeof(char *) * (env_lst_len(env_list) + 1));
	if (!to_return)
		return (NULL);
	i = 0;
	while (env_list != NULL)
	{
		to_return[i] = malloc(sizeof(char)
				* (ft_strlen(env_list->key) + ft_strlen(env_list->value) + 2));
		if (!to_return[i])
		{
			while (i >= 0)
				free(to_return[i--]);
			free(to_return);
			return (NULL);
		}
		env_array_keyvalue(to_return[i], env_list);
		i++;
		env_list = env_list->next;
	}
	to_return[i] = NULL;
	return (to_return);
}
