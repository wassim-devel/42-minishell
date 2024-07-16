/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 10:19:06 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/22 15:05:08 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	replace_by_env(char *to_return, const char *str,
			size_t j, t_envlst *envlst)
{
	size_t	k;
	char	*env_value;
	char	*variable;

	variable = grab_variable(str);
	env_value = env_get_value(envlst, variable);
	free(variable);
	if (!env_value)
		return (0);
	k = 0;
	while (env_value[k])
	{
		if (env_value[k] == '"' || env_value[k] == '\'')
			to_return[j] = env_value[k] - 10;
		else
			to_return[j] = env_value[k];
		j++;
		k++;
	}
	return (k);
}

size_t	len_without_quotes(const char *str)
{
	size_t	i;
	size_t	count;
	bool	single_quote_flag;
	bool	double_quote_flag;

	i = 0;
	count = 0;
	single_quote_flag = 0;
	double_quote_flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && double_quote_flag == 0)
			single_quote_flag = !single_quote_flag;
		else if (str[i] == '"' && single_quote_flag == 0)
			double_quote_flag = !double_quote_flag;
		else
			count++;
		i++;
	}
	return (count);
}

void	string_expansion_loop(const char *str, t_envlst *envlst,
				char *to_return, int flag)
{
	ssize_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		flag = set_flag(str[i], flag);
		while (str[i] == '$' && ft_isdigit(str[i + 1]) && flag != 1)
			i += 2;
		while (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
			&& flag != 1)
		{
			j += replace_by_env(to_return, &str[i + 1], j, envlst);
			i += len_for_variable(str, i + 1) + 1;
		}
		if (!str[i])
			break ;
		to_return[j] = str[i];
		j++;
	}
	to_return[j] = '\0';
}

char	*expand_variables(const char *str, t_envlst *envlst)
{
	char	*to_return;
	int		flag;

	to_return = malloc(sizeof(char) * (ft_strlen(str)
				+ len_of_variables_values(str, envlst)
				- len_of_variables(str) + 1));
	if (!to_return)
		return (NULL);
	flag = 0;
	string_expansion_loop(str, envlst, to_return, flag);
	return (to_return);
}
