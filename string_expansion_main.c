/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_expansion_main.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:06:10 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/23 10:43:59 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	number_of_interr(const char *str)
{
	size_t	i;
	size_t	count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (str[i])
	{
		flag = set_flag(str[i], flag);
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '?' && flag != 1)
			count++;
		i++;
	}
	return (count);
}

void	expand_interr_loop(const char *str, char *to_return,
		char *last_status_str, size_t i)
{
	size_t	j;
	size_t	k;
	int		flag;

	j = 0;
	k = 0;
	flag = 0;
	while (str[++i])
	{
		flag = set_flag(str[i], flag);
		while (str[i] && str[i + 1] && str[i] == '$'
			&& str[i + 1] == '?' && flag != 1)
		{
			i += 2;
			while (last_status_str[k])
			{
				to_return[j++] = last_status_str[k++];
			}
			k = 0;
		}
		if (!str[i])
			break ;
		to_return[j++] = str[i];
	}
	to_return[j] = '\0';
}

char	*string_expansion(const char *str, t_envlst *envlst, int last_status)
{
	char	*last_status_str;
	char	*to_return;
	char	*to_return_w_variables;
	size_t	i;

	i = -1;
	last_status_str = ft_itoa(last_status);
	if (!last_status_str)
		return (NULL);
	to_return = malloc(sizeof(char) * (ft_strlen(last_status_str)
				* number_of_interr(str) + ft_strlen(str)
				- (number_of_interr(str) * 2) + 1));
	if (!to_return)
		return (NULL);
	expand_interr_loop(str, to_return, last_status_str, i);
	to_return_w_variables = expand_variables(to_return, envlst);
	free(to_return);
	free(last_status_str);
	return (to_return_w_variables);
}

int	expand_line(t_shell *shell)
{
	char	*old_line;

	old_line = shell->line;
	shell->line = string_expansion(shell->line, shell->envlst,
			shell->last_status);
	free(old_line);
	if (!shell->line)
		return (-1);
	return (0);
}
