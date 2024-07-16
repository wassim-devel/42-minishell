/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:52:13 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/09 13:56:58 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_lst_len(t_envlst *env_list)
{
	size_t	count;

	count = 0;
	if (env_list == NULL)
		return (0);
	while (env_list != NULL)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

void	env_putkey(char *keyvalue, char *elem_key)
{
	size_t	i;

	i = 0;
	while (keyvalue[i] && keyvalue[i] != '=')
	{
		elem_key[i] = keyvalue[i];
		i++;
	}
	elem_key[i] = '\0';
}

void	env_putvalue(char *keyvalue, char *elem_value)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (keyvalue[i] && keyvalue[i] != '=')
		i++;
	if (keyvalue[i] == '=')
		i++;
	while (keyvalue[i] && keyvalue[i] != '=')
	{
		elem_value[j] = keyvalue[i];
		i++;
		j++;
	}
	elem_value[j] = '\0';
}

void	env_destroy(t_envlst *envlst)
{
	t_envlst	*curr_elem;
	t_envlst	*next_elem;

	curr_elem = envlst;
	while (curr_elem)
	{
		free(curr_elem->key);
		free(curr_elem->value);
		next_elem = curr_elem->next;
		free(curr_elem);
		curr_elem = next_elem;
	}
}
