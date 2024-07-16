/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:51 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/18 14:33:06 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	len_for_variable(const char *str, size_t i)
{
	size_t	count;

	count = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		count++;
		i++;
	}
	return (count);
}

char	*grab_variable(const char *str)
{
	size_t	i;
	char	*variable;

	i = 0;
	variable = malloc(sizeof(char) * (len_for_variable(str, i) + 1));
	if (!variable)
		return (NULL);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		variable[i] = str[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

size_t	len_of_variables(const char *str)
{
	size_t	i;
	size_t	count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && flag == 0)
			flag = 1;
		else if (str[i] == '\'' && flag == 1)
			flag = 0;
		if (str[i] == '"' && flag == 0)
			flag = 2;
		else if (str[i] == '"' && flag == 2)
			flag = 0;
		if (str[i] == '$' && (ft_isalpha(str[i + 1])
				|| str[i + 1] == '_') && flag != 1)
		{
			count += len_for_variable(str, i + 1) + 1;
		}
		i++;
	}
	return (count);
}

size_t	len_of_variables_values(const char *s, t_envlst *envlst)
{
	ssize_t	i;
	size_t	count;
	char	*variable_value;
	char	*variable;
	int		f;

	i = -1;
	count = 0;
	f = 0;
	while (s[++i])
	{
		f = set_flag(s[i], f);
		if (s[i] == '$' && ft_isdigit(s[i + 1]) && f != 1)
			i += 2;
		else if (s[i] == '$' && (ft_isalpha(s[i + 1])
				|| s[i + 1] == '_') && f != 1)
		{
			variable = grab_variable(&s[i + 1]);
			variable_value = env_get_value(envlst, variable);
			free(variable);
			if (variable_value)
				count += ft_strlen(variable_value);
		}
	}
	return (count);
}

int	set_flag(const char c, int flag)
{
	if (c == '\'' && flag == 0)
		flag = 1;
	else if (c == '\'' && flag == 1)
		flag = 0;
	if (c == '"' && flag == 0)
		flag = 2;
	else if (c == '"' && flag == 2)
		flag = 0;
	return (flag);
}
