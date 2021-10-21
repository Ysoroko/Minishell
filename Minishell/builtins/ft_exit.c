/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:57:11 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/21 14:53:15 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_exit_error(char *str, char *str2)
{
	ft_putendl_fd("exit", STDOUT);
	ft_putstr_fd(PROMPT_NAME, STDERR);
	ft_putstr_fd("exit: ", STDERR);
	ft_putstr_fd(str, STDERR);
	if (str2)
		ft_putstr_fd(str2, STDERR);
	ft_putchar_fd('\n', STDERR);
}

void	ft_exit(int n)
{
	char	*temp;
	char	*n_str;

	n_str = ft_itoa_exit(n);
	temp = ft_strjoin_exit("EXIT_STATUS=", n_str);
	g_glob.exit_status = n;
	g_glob.env = ft_export(temp);
	free(n_str);
	free(temp);
	exit(n);
}

// Possible bad arguments:
// 1) Non num argument [bash: exit: exit: numeric argument required] [$? = 255]
//	Will exit anyway,then display an error message
// 2) >1 argument [bash: exit: too many arguments] [$? = 1]
void	ft_exit_cmd(t_command *cmd)
{
	int		exit_arg;
	char	*exit_arg_str;

	exit_arg_str = cmd->str_tab_for_execve[1];
	if (ft_str_tab_len(cmd->str_tab_for_execve) > 2)
	{
		ft_exit_error("too many arguments", NULL);
		g_glob.env = ft_export("EXIT_STATUS=1");
	}
	else if (!(ft_str_only_has_chars_from_charset(exit_arg_str, "0123456789")))
	{
		ft_exit_error(exit_arg_str, ": numeric argument required");
		ft_exit(1);
	}
	else
	{
		exit_arg = ft_atoi(exit_arg_str);
		ft_exit(exit_arg);
	}
}
