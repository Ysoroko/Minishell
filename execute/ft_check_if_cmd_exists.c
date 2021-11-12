/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_cmd_exists.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:26:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/12 15:07:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_binary(char *filename)
{
	struct stat	sb;

	if (!filename || !filename[0])
		return (-1);
	if (stat(filename, &sb) == 0)
	{
		if (sb.st_mode & S_IXUSR)
			return (1);
	}
	return (-1);
}

int	ft_builtin_cmd_no_path(char *exec_name)
{
	if (ft_strcmp("cd", exec_name) == 0)
		return (0);
	if (ft_strcmp("export", exec_name) == 0)
		return (1);
	if (ft_strcmp("unset", exec_name) == 0)
		return (2);
	if (ft_strcmp("exit", exec_name) == 0)
		return (3);
	if (ft_strcmp("echo", exec_name) == 0)
		return (4);
	if (ft_strcmp("pwd", exec_name) == 0)
		return (5);
	if (ft_strcmp("env", exec_name) == 0)
		return (6);
	if (ft_strcmp("minishell", exec_name) == 0)
		return (7);
	return (-1);
}

void	ft_path_error(t_command *command)
{
	if (ft_set_paths(&command->str_tab_for_execve[0]) == -1
		&& command->error == 0)
	{
		ft_err(command->str_tab_for_execve[0], NULL, strerror(errno),
			127);
		command->error = 1;
		command->exists = 0;
	}
}

void	ft_check_if_cmd_exists(t_command *command)
{
	if (ft_builtin_cmd_no_path(command->str_tab_for_execve[0]) != -1)
		return ;
	if (ft_check_binary(command->str_tab_for_execve[0]) != 1)
		ft_path_error(command);
	if (ft_check_binary(command->str_tab_for_execve[0]) == 1)
		command->exists = 1;
	else
	{
		if (ft_builtin_cmd_found(command->str_tab_for_execve[0]) == 0
			&& command->error == 0)
		{
			if (command->redir_type_in == 0 && command->redir_type_out == 0)
				ft_minishell_error("command not found");
			command->error = 1;
			command->exists = 1;
		}
	}
}
