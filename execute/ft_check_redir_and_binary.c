/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_and_binary.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:41:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/12 15:04:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_file_permissions(char *filename)
{
	struct stat	sb;

	if (!filename)
		return (-1);
	if (stat(filename, &sb) == 0)
	{
		if (sb.st_mode & S_IRUSR && sb.st_mode & S_IWUSR)
			return (1);
		else if (sb.st_mode & S_IWUSR)
			return (2);
		else if (sb.st_mode & S_IRUSR)
			return (3);
		return (0);
	}
	return (-1);
}

void	ft_add_redir_files(t_command *cmd, int m, int i)
{
	if (m == REDIR_R || m == REDIR_RR)
		ft_add_redir_out(cmd, m, i);
	else if (m == REDIR_L || m == REDIR_LL)
	{
		if (m == REDIR_L)
			ft_add_redir_in(cmd, i);
		else if (m == REDIR_LL)
			ft_add_redir_hdoc(cmd, i);
	}
	return ;
}

int	ft_exec_check(char *path, char *cmd)
{
	int				i;
	DIR				*dir;
	struct dirent	*d;

	i = 0;
	if (cmd == NULL)
		return (-1);
	dir = opendir(path);
	if (!dir)
		return (-1);
	d = readdir(dir);
	while (d != NULL)
	{
		if (strcmp(cmd, d->d_name) == 0)
		{
			closedir(dir);
			return (1);
		}
		d = readdir(dir);
	}
	closedir(dir);
	return (-1);
}

void	ft_check_tables(t_command *command)
{
	command->keyword = (char **)ft_malloc_exit(sizeof(char *) * 12);
	if (!command->keyword && command->error == 0)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
}

void	ft_check_redir_and_binary(void *current_command)
{
	t_command	*command;
	int			m;
	int			i;

	i = -1;
	command = (t_command *)(current_command);
	ft_check_tables(command);
	ft_check_if_cmd_exists(command);
	command->keyword_index = 0;
	while (command->str_tab_all[++i])
	{
		m = (command->role_macros)[i];
		ft_add_redir_files(command, m, i);
	}
	if (command->str_tab_for_execve[0] == NULL && command->error == 0)
	{
		command->error = 1;
		command->exists = 0;
		if (command->redir_type_in == 0 && command->redir_type_out == 0)
			ft_minishell_error("command not found");
	}
}
