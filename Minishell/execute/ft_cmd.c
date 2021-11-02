/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:14:45 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/02 11:51:04 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_builtin_cmd_found(char *exec_name)
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

int	ft_cmd_handler(t_command *cmd)
{
	char	*tmp;
	char	*path;

	path = cmd->path;
	tmp = cmd->str_tab_for_execve[0];
	if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 4)
		cmd->str_tab_for_execve[0] = ft_strjoin_exit(path, "./ft_echo");
	if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 5)
		cmd->str_tab_for_execve[0] = ft_strjoin_exit(path, "./ft_pwd");
	if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 6)
		cmd->str_tab_for_execve[0] = ft_strjoin_exit(path, "./ft_env");
	free(tmp);
	if (execve(cmd->str_tab_for_execve[0],
			cmd->str_tab_for_execve, g_glob.env) == -1)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	return (-1);
}

void	ft_cmd_handler_no_fork(t_command *cmd, int s)
{
	if (s == 0)
		ft_cd(cmd);
	if (s == 1)
		ft_export_handler(cmd);
	if (s == 2)
		ft_unset_handler(cmd);
	if (s == 3)
	{
		ft_down_shlvl();
		ft_exit_cmd(cmd);
	}
}

void	ft_pipe_cmd(t_dl_lst *command_list, t_command *cmd, int *pfd, int j)
{
	if (command_list->next)
	{
		if (cmd->redir_type_out != REDIR_R && cmd->redir_type_out != REDIR_RR)
		{
			if (dup2(pfd[j + 1], 1) == -1)
			{
				ft_minishell_error(strerror(errno));
				ft_exit(errno);
			}
		}
	}
	if (j != 0)
	{
		if (cmd->redir_type_in != REDIR_L && cmd->redir_type_in != REDIR_LL)
		{
			if (dup2(pfd[j - 2], 0) == -1)
			{
				ft_minishell_error(strerror(errno));
				ft_exit(errno);
			}
		}
	}
}

void	ft_fds_and_pipes(t_dl_lst *lst, t_command *cmd, int *pfd, int j)
{
	if (cmd->redir_type_in == REDIR_L || cmd->redir_type_in == REDIR_LL)
		ft_fdin(cmd);
	if (cmd->redir_type_out == REDIR_R || cmd->redir_type_out == REDIR_RR)
		ft_fdout(cmd);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->infile)
		free(cmd->infile);
	ft_pipe_cmd(lst, cmd, pfd, j);
}
