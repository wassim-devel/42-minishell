/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:50:08 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/23 10:39:05 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envlst	*env_elem_create(char *keyvalue)
{
	t_envlst	*env_elem;
	size_t		key_len;
	size_t		val_len;

	key_len = 0;
	val_len = 0;
	env_elem = ft_calloc(1, sizeof(t_envlst));
	if (!env_elem)
		return (NULL);
	if (!ft_strchr(keyvalue, '='))
		env_elem->only_export = 1;
	while (keyvalue[key_len] && keyvalue[key_len] != '=')
		key_len++;
	env_elem->key = ft_calloc(key_len + 1, sizeof(char));
	if (!env_elem->key)
		return (free(env_elem), NULL);
	while (keyvalue[key_len + val_len])
		val_len++;
	env_elem->value = ft_calloc(val_len + 1, sizeof(char));
	if (!env_elem)
		return (free(env_elem->key), free(env_elem), NULL);
	env_putkey(keyvalue, env_elem->key);
	env_putvalue(keyvalue, env_elem->value);
	return (env_elem);
}

int	env_lst_add(t_envlst **envlst, char *keyvalue)
{
	t_envlst	*new_env_elem;
	t_envlst	*last_env_elem;

	if (!keyvalue)
		return (-1);
	new_env_elem = env_elem_create(keyvalue);
	if (!new_env_elem)
		return (-1);
	if (!(*envlst))
	{
		*envlst = new_env_elem;
		return (0);
	}
	last_env_elem = *envlst;
	while (last_env_elem->next)
		last_env_elem = last_env_elem->next;
	last_env_elem->next = new_env_elem;
	return (0);
}

t_envlst	*env_lst_copy(char **env)
{
	int			i;
	t_envlst	*env_lst;

	i = 0;
	env_lst = NULL;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (env_lst_add(&env_lst, env[i]) == -1)
			return (env_destroy(env_lst), NULL);
		i++;
	}
	return (env_lst);
}
