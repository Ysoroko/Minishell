/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redir_and_binary.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:41:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/25 15:54:24 by ysoroko          ###   ########.fr       */
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

void	ft_hdoc(t_command *cmd)
{
	int	fd;

	if (ft_check_file_permissions("hdoc/tmp") >= 1)
		fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	else
		fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		cmd->buffer = readline("> ");
		if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) == 0)
		{
			if (close(fd) == -1)
				exit(EXIT_FAILURE);
			return ;
		}
		write(fd, cmd->buffer, ft_strlen(cmd->buffer));
		write(fd, "\n", 1);
	}
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}

void	ft_add_redir_out(t_command *cmd, int m, int i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->str_tab_all[i + 1] != NULL)
		cmd->outfile = ft_strdup(cmd->str_tab_all[i + 1]);
	else
		exit(EXIT_FAILURE);
	if (!cmd->outfile)
		exit(EXIT_FAILURE);
	if (m == REDIR_R)
	{
		cmd->fdout = open(cmd->outfile, O_CREAT | O_TRUNC, 0664);
		cmd->redir_type_out = 1;
	}
	else
	{
		cmd->fdout = open(cmd->outfile, O_CREAT | O_APPEND, 0664);
		cmd->redir_type_out = 2;
	}
	if (cmd->fdout == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (close(cmd->fdout) == -1)
		exit(EXIT_FAILURE);
}

void	ft_add_redir_in(t_command *cmd, int m, int i)
{
	cmd->redir_type_in = 3;
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->str_tab_all[i + 1] != NULL)
		cmd->infile = ft_strdup(cmd->str_tab_all[i + 1]);
	else
		exit(EXIT_FAILURE);
	if (!cmd->infile)
		exit(EXIT_FAILURE);
	cmd->fdin = open(cmd->infile, O_RDONLY);
	if (cmd->fdin == -1)
		exit(EXIT_FAILURE);
	if (close(cmd->fdin) == -1)
		exit(EXIT_FAILURE);
}

void	ft_add_redir_hdoc(t_command *cmd, int m, int i)
{
	cmd->redir_type_in = 4;
	if (cmd->str_tab_all[i + 1] != NULL)
		cmd->keyword[cmd->keyword_index] = ft_strdup(cmd->str_tab_all[i + 1]);
	else
		exit(EXIT_FAILURE);
	if (!cmd->keyword[cmd->keyword_index])
		exit(EXIT_FAILURE);
	ft_hdoc(cmd);
	cmd->keyword_index++;
	cmd->keyword[cmd->keyword_index] = 0;
}

void	ft_add_redir_file(t_command *cmd, int m, int i)
{
	if (m == REDIR_R || m == REDIR_RR)
		ft_add_redir_out(cmd, m, i);
	else if (m == REDIR_L || m == REDIR_LL)
	{
		if (m == REDIR_L)
			ft_add_redir_in(cmd, m, i);
		else if (m == REDIR_LL)
			ft_add_redir_hdoc(cmd, m, i);
	}
	return ;
}

int	ft_exec_check(char *path, char *cmd)
{
	int				i;
	DIR				*dir;
	struct dirent	*d;
	char			*tmp;

	i = 0;
	dir = opendir(path);
	d = readdir(dir);
	while (d != NULL)
	{
		if (strcmp(cmd, d->d_name) == 0)
			return (1);
		d = readdir(dir);
	}
	closedir(dir);
	return (-1);
}

int	ft_set_paths(char **exec_name)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = -1;
	tmp = getenv("PATH");
	if (!tmp)
		return (-1);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (-1);
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin_exit(paths[i], "/");
		free(tmp);
		if (ft_exec_check(paths[i], *exec_name) == 1)
		{
			tmp = *exec_name;
			*exec_name = ft_strjoin_exit(paths[i], *exec_name);
			free(tmp);
			return (1);
		}
	}
	return (0);
}

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

void	ft_check_redir_and_binary(void *current_command)
{
	t_command	*command;
	int			m;
	int			i;

	i = -1;
	command = (t_command *)(current_command);
	if (!command || !command->str_tab_all || !command->str_tab_all[0]
		|| !command->str_tab_for_execve || ! command->str_tab_for_execve[0]
		|| !command->role_macros || !command->role_macros[0])
	{
		return ;
	}
	command->keyword = (char **)malloc(sizeof(char *) * 1024);
	if (!command->keyword)
		exit(EXIT_FAILURE);
	command->keyword_index = 0;
	while (command->str_tab_all[++i])
	{
		m = (command->role_macros)[i];
		if (ft_is_a_redir_arg_macro(m))
			ft_add_redir_file(command, m, i);
	}
	if (ft_check_binary(command->str_tab_for_execve[0]) != 1)
	{
		if (ft_set_paths(&command->str_tab_for_execve[0]) == -1)
			exit(EXIT_FAILURE);
	}
}
