/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_if_cmd_exists.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:26:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 06:26:58 by ablondel         ###   ########.fr       */
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
			command->error = 1;
			printf("minishell: %s: command not found\n",
				command->str_tab_for_execve[0]);
		}
	}
	if (ft_check_binary(command->str_tab_for_execve[0]) == 1)
		command->exists = 1;
	else
	{
		if (ft_builtin_cmd_found(command->str_tab_for_execve[0]) == 0
			&& command->error == 0)
		{
			printf("minishell: %s: command not found\n",
				command->str_tab_for_execve[0]);
			command->error = 1;
			command->exists = 0;
		}
	}
}
