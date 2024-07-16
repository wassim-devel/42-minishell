/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoizel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:54:57 by aoizel            #+#    #+#             */
/*   Updated: 2024/01/23 10:45:24 by wlalaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_value(t_envlst *envlst_elem, char *keyvalue, size_t key_len)
{
	if (ft_strchr(keyvalue, '='))
	{
		free(envlst_elem->value);
		envlst_elem->value
			= ft_calloc(ft_strlen(keyvalue) - key_len, sizeof(char));
		if (!envlst_elem->value)
			return (-1);
		envlst_elem->only_export = 0;
		env_putvalue(keyvalue, envlst_elem->value);
	}
	return (0);
}

int	env_set_value(t_envlst **envlst, char *keyvalue)
{
	size_t		key_len;
	t_envlst	*envlst_elem;

	if (!keyvalue)
		return (-1);
	key_len = 0;
	while (keyvalue[key_len] && keyvalue[key_len] != '=')
		key_len++;
	envlst_elem = *envlst;
	while (envlst_elem && !(ft_strlen(envlst_elem->key) == key_len
			&& ft_strncmp(envlst_elem->key, keyvalue, key_len) == 0))
		envlst_elem = envlst_elem->next;
	if (envlst_elem)
	{
		if (set_value(envlst_elem, keyvalue, key_len) == -1)
			return (-1);
	}
	else
		return (env_lst_add(envlst, keyvalue));
	return (0);
}

char	*env_get_value(t_envlst *envlst, char *key)
{
	if (!key)
		return (NULL);
	while (envlst)
	{
		if (ft_strcmp(envlst->key, key) == 0)
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}
