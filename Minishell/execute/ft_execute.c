/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/29 15:11:11 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close_pipes(int npipes, int *pfd)
{
	int	i;

	i = 0;
	while (i < (npipes * 2))
	{
		if (close(pfd[i]) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	ft_open_pipes(int npipes, int *pfd)
{
	int	i;

	i = 0;
	while (i < npipes)
	{
		if (pipe(pfd + i * 2) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	ft_fdin(t_command *cmd)
{
	if (cmd->redir_type_in == REDIR_L)
		cmd->fdin = open(cmd->infile, O_RDONLY);
	else
		cmd->fdin = open("hdoc/tmp", O_RDONLY);
	if (cmd->fdin == -1)
		exit(EXIT_FAILURE);
	if (dup2(cmd->fdin, 0) == -1)
		exit(EXIT_FAILURE);
	if (close(cmd->fdin) == -1)
		exit(EXIT_FAILURE);
}

void	ft_fdout(t_command *cmd)
{
	if (cmd->redir_type_out == REDIR_R)
		cmd->fdout = open(cmd->outfile, O_RDWR | O_TRUNC, 0664);
	else
		cmd->fdout = open(cmd->outfile, O_RDWR | O_APPEND, 0664);
	if (cmd->fdout == -1)
		exit(EXIT_FAILURE);
	if (dup2(cmd->fdout, 1) == -1)
		exit(EXIT_FAILURE);
	if (close(cmd->fdout) == -1)
		exit(EXIT_FAILURE);
}

void	ft_pipe_cmd(t_dl_lst *command_list, t_command *cmd, int *pfd, int j)
{
	if (command_list->next)
		if (cmd->redir_type_out != REDIR_R || cmd->redir_type_out != REDIR_RR)
			if (dup2(pfd[j + 1], 1) == -1)
				exit(EXIT_FAILURE);
	if (j != 0)
		if (cmd->redir_type_in != REDIR_L || cmd->redir_type_in != REDIR_LL)
			if (dup2(pfd[j - 2], 0) == -1)
				exit(EXIT_FAILURE);
}

void	ft_setup_for_exec(t_dl_lst *lst, int **pfd, int *npipes)
{
	*npipes = ft_lstsize((t_list *)lst) - 1;
	*pfd = (int *)malloc(sizeof(int) * (*npipes * 2));
	if (!(*pfd))
		exit(EXIT_FAILURE);
	//ft_dl_lstiter(lst, ft_print_command_list);
	ft_dl_lstiter(lst, ft_check_redir_and_binary);
	ft_open_pipes(*npipes, *pfd);
}

void	ft_fds_and_pipes(t_dl_lst *lst, t_command *cmd, int *pfd, int j)
{
	if (cmd->redir_type_in == REDIR_L || cmd->redir_type_in == REDIR_LL)
		ft_fdin(cmd);
	if (cmd->redir_type_out == REDIR_R || cmd->redir_type_out == REDIR_RR)
		ft_fdout(cmd);
	ft_pipe_cmd(lst, cmd, pfd, j);
}

void	ft_parent_process(int npipes, int *pfd)
{
	int	i;

	i = 0;
	ft_close_pipes(npipes, pfd);
	while (i <= npipes)
	{
		wait(NULL);
		i++;
	}
}

void	ft_execute(t_dl_lst *command_list)
{
	t_command	*cmd;
	int			*pfd;
	int			npipes;
	int			j;

	ft_setup_for_exec(command_list, &pfd, &npipes);
	j = 0;
	while (command_list)
	{
		cmd = (t_command *)command_list->content;
		g_glob.fork_ret = fork();
		if (g_glob.fork_ret < 0)
			exit(EXIT_FAILURE);
		if (g_glob.fork_ret == 0)
		{
			ft_fds_and_pipes(command_list, cmd, pfd, j);
			ft_close_pipes(npipes, pfd);
			execve(cmd->str_tab_for_execve[0], cmd->str_tab_for_execve, g_glob.env);
		}
		command_list = command_list->next;
		j += 2;
	}
	ft_parent_process(npipes, pfd);
}
