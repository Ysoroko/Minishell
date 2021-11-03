/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/03 13:49:51 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_setup_for_exec(t_dl_lst *lst, int **pfd, int *npipes, int *j)
{
	*j = 0;
	*npipes = ft_lstsize((t_list *)lst) - 1;
	*pfd = (int *)malloc(sizeof(int) * (*npipes * 2));
	if (!(*pfd))
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	ft_dl_lstiter(lst, ft_check_redir_and_binary);
	ft_open_pipes(*npipes, *pfd);
}

void	ft_parent_process(int npipes, int *pfd)
{
	int	i;
	int	status;
	int	status_code;

	i = 0;
	while (i <= npipes)
	{
		waitpid(0, &status, 0);
		if (g_glob.fork_ret > 0)
		{
			if (WIFEXITED(status))
			{
				status_code = WEXITSTATUS(status);
				ft_modify_exit_status(status_code);
			}
			else if (WIFSIGNALED(status))
			{
				status_code = 128 + WTERMSIG(status);
				ft_modify_exit_status(status_code);
			}
		}
		i++;
	}
	ft_display_signal_message(status_code);
	free(pfd);
}

void	ft_pipe_and_exec(t_dl_lst *lst, int *pfd, int j, int npipes)
{
	t_command	*cmd;

	cmd = (t_command *)lst->content;
	ft_fds_and_pipes(lst, cmd, pfd, j);
	ft_close_pipes(npipes, pfd);
	if (cmd->s >= 4 && cmd->s <= 6)
		ft_cmd_handler(cmd);
	else
	{
		if (cmd->error == 0)
		{
			if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 7)
				ft_up_shlvl();
			else if (execve(cmd->str_tab_for_execve[0],
					cmd->str_tab_for_execve, g_glob.env) == -1)
			{
				ft_minishell_error(strerror(errno));
				ft_exit(errno);
			}
		}
	}
}

void	ft_handle_cmd(t_dl_lst *lst, int *pfd, int j, int npipes)
{
	t_command	*cmd;

	cmd = (t_command *)lst->content;
	if (cmd->s >= 0 && cmd->s <= 3)
		ft_cmd_handler_no_fork(cmd, cmd->s);
	else
	{
		g_glob.fork_ret = fork();
		if (g_glob.fork_ret < 0)
			ft_exit_cmd(cmd);
		if (g_glob.fork_ret == 0)
			ft_pipe_and_exec(lst, pfd, j, npipes);
	}
}

void	ft_execute(t_dl_lst *command_list)
{
	t_command	*cmd;
	int			*pfd;
	int			npipes;
	int			j;

	ft_setup_for_exec(command_list, &pfd, &npipes, &j);
	while (command_list)
	{
		cmd = (t_command *)command_list->content;
		if (cmd->error == 0)
		{
			cmd->s = ft_builtin_cmd_found(cmd->str_tab_for_execve[0]);
			if (cmd->s >= 0 && cmd->s <= 6)
				cmd->exists = 1;
			if (cmd->exists == 1 && cmd->error == 0)
				ft_handle_cmd(command_list, pfd, j, npipes);
			else if (cmd->error == 0)
				ft_err(cmd->str_tab_for_execve[0], 0, "command not found", 127);
		}
		ft_free_ressources(cmd);
		command_list = command_list->next;
		j += 2;
	}
	ft_close_pipes(npipes, pfd);
	ft_parent_process(npipes, pfd);
}
