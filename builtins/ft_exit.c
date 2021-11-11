/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:57:11 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/11 16:29:13 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_exit_error(char *str, char *str2)
{
	ft_putstr_fd(PROMPT_ERROR, STDERR);
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(str, STDERR);
	if (str2)
		ft_putstr_fd(str2, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_exit(int n)
{
	ft_modify_exit_status(n);
	exit(n);
}

// Possible bad arguments:
// 1) Non num argument [bash: exit: exit: numeric argument required] [$? = 255]
//	Will exit anyway,then display an error message
// 2) >1 argument [bash: exit: too many arguments] [$? = 1]
// 3) ./minishell à l'intérieur du minishell -> crée un 2e "EXIT_STATUS"
void	ft_exit_cmd(t_command *cmd)
{
	int		exit_arg;
	char	*exit_arg_str;
	int		non_num;

	ft_putendl_fd("exit", STDOUT);
	exit_arg_str = cmd->str_tab_for_execve[1];
	non_num = !ft_str_only_has_chars_from_charset(exit_arg_str, "0123456789");
	if (exit_arg_str && non_num)
	{
		ft_exit_error(exit_arg_str, ": numeric argument required");
		ft_exit(255);
	}
	else if (ft_str_tab_len(cmd->str_tab_for_execve) > 2)
	{
		ft_exit_error("too many arguments", NULL);
		ft_modify_exit_status(1);
	}
	else
	{
		exit_arg = ft_atoi(exit_arg_str);
		ft_exit(exit_arg);
	}
}
