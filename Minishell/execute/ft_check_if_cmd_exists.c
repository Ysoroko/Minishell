/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_cmd_exists.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:26:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/21 16:53:57 by ysoroko          ###   ########.fr       */
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

void	ft_check_if_cmd_exists(t_command *command)
{
	if (ft_check_binary(command->str_tab_for_execve[0]) != 1)
	{
		if (ft_set_paths(&command->str_tab_for_execve[0]) == -1
			&& command->error == 0)
		{
			ft_minishell_error("command not found");
			command->error = 1;
			command->exists = 0;
		}
	}
	if (ft_check_binary(command->str_tab_for_execve[0]) == 1)
		command->exists = 1;
	else
	{
		if (ft_builtin_cmd_found(command->str_tab_for_execve[0]) == 0
			&& command->error == 0)
		{
			ft_minishell_error("command not found");
			command->error = 1;
			command->exists = 1;
		}
	}
}
