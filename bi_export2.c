/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:30:38 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/22 11:58:17 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_array_keyvalue_e(char *to_return, t_envlst *env_list)
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
	if (env_list->only_export == 0)
		to_return[k++] = '=';
	j = 0;
	if (env_list->only_export == 0)
		to_return[k++] = '"';
	while (env_list->value[j])
	{
		to_return[k] = env_list->value[j];
		k++;
		j++;
	}
	if (env_list->only_export == 0)
		to_return[k++] = '"';
	to_return[k] = '\0';
}

char	**array_convert_for_export(t_envlst *env_list)
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
				* (ft_strlen(env_list->key) + ft_strlen(env_list->value) + 4));
		if (!to_return[i])
		{
			while (i >= 0)
				free(to_return[i--]);
			free(to_return);
			return (NULL);
		}
		env_array_keyvalue_e(to_return[i], env_list);
		i++;
		env_list = env_list->next;
	}
	to_return[i] = NULL;
	return (to_return);
}
