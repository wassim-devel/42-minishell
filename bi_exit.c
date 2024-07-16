/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlalaoui <wlalaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:07:55 by wlalaoui          #+#    #+#             */
/*   Updated: 2024/01/19 11:12:03 by aoizel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_envlst(t_envlst **envlst)
{
	t_envlst	*temp;
	t_envlst	*curr;

	if (!envlst || !*envlst)
		return ;
	curr = *envlst;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp->value);
		free(temp->key);
		free(temp);
	}
	*envlst = NULL;
}

int	free_shell(t_shell *shell_to_free)
{
	int	ret;

	ret = clean_processlst(&shell_to_free->processlst, shell_to_free);
	clean_wordlst(&shell_to_free->wordlst);
	clean_envlst(&shell_to_free->envlst);
	free_envarray(shell_to_free->envarray);
	free(shell_to_free->line);
	free(shell_to_free->prompt);
	free(shell_to_free);
	rl_clear_history();
	return (ret);
}

void	check_digits(char **args, t_shell *shell_to_free, int fd_out)
{
	size_t	i;

	i = 1;
	if (!ft_isdigit(args[1][0]) && !(args[1][0] == '+' || args[1][0] == '-'))
	{
		ft_putstr_fd("exit\n", fd_out);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_shell(shell_to_free);
		exit(2);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd("exit\n", fd_out);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			free_shell(shell_to_free);
			exit(2);
		}
		i++;
	}
}

int	piped_check_digits(char **args)
{
	size_t	i;

	i = 1;
	if (!args[1])
		return (0);
	if (args[2])
		return (ft_putstr_fd("exit: too many arguments\n", 2), 2);
	if (!ft_isdigit(args[1][0]) && !(args[1][0] == '+' || args[1][0] == '-'))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		return (ft_putstr_fd(": numeric argument required\n", 2), 2);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i++]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			return (ft_putstr_fd(": numeric argument required\n", 2), 2);
		}
	}
	return (ft_atoi(args[1]));
}

int	bi_exit(t_shell *shell_to_free, char **args, int is_piped)
{
	int	number;

	if (!is_piped)
	{
		if (!args || !args[1])
		{
			number = free_shell(shell_to_free);
			ft_putstr_fd("exit\n", 1);
			exit(number & 255);
		}
		check_digits(args, shell_to_free, 1);
		if (args[2])
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		number = ft_atoi(args[1]);
		free_shell(shell_to_free);
		ft_putstr_fd("exit\n", 1);
		exit(number & 255);
	}
	return (piped_check_digits(args));
}
