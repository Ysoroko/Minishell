/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/08 08:13:53 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_setup_for_exec(t_dl_lst *lst, int **pfd, int *npipes)
{
	*npipes = ft_lstsize((t_list *)lst) - 1;
	*pfd = (int *)malloc(sizeof(int) * (*npipes * 2));
	if (!(*pfd))
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
	ft_dl_lstiter(lst, ft_check_redir_and_binary);
	ft_open_pipes(*npipes, *pfd);
}

void	ft_parent_process(int npipes, int *pfd)
{
	int	i;

	i = 0;
	ft_close_pipes(npipes, pfd);
	while (i <= npipes + 1)
	{
		wait(NULL);
		i++;
	}
}

void	ft_child_process(t_dl_lst *lst, t_command *cmd, int *pfd, int j)
{
	int	npipes;

	npipes = ft_lstsize((t_list *)lst) - 1;
	ft_fds_and_pipes(lst, cmd, pfd, j);
	ft_close_pipes(npipes, pfd);
	if (cmd->s >= 4 && cmd->s <= 6)
		ft_cmd_handler(cmd);
	else
	{
		if (cmd->error == 0)
		{
			if (execve(cmd->str_tab_for_execve[0],
					cmd->str_tab_for_execve, g_glob.env) == -1)
			{
				printf("minishell: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	}
}

void	ft_select_action(t_dl_lst *lst, t_command *cmd, int *pfd, int j)
{
	if (cmd->s >= 0 && cmd->s <= 3)
		ft_cmd_handler_no_fork(cmd, cmd->s);
	else
	{
		g_glob.fork_ret = fork();
		if (g_glob.fork_ret < 0)
			exit(EXIT_FAILURE);
		if (g_glob.fork_ret == 0)
		{
			ft_fds_and_pipes(lst, cmd, pfd, j);
			ft_close_pipes(ft_lstsize((t_list *)lst) - 1, pfd);
			if (cmd->s >= 4 && cmd->s <= 6)
				ft_cmd_handler(cmd);
			else
			{
				if (cmd->error == 0)
				{
					if (execve(cmd->str_tab_for_execve[0],
							cmd->str_tab_for_execve, g_glob.env) == -1)
					{
						printf("minishell: %s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
}

void	ft_execute(t_dl_lst *command_list)
{
	t_command	*cmd;
	int			*pfd;
	int			npipes;
	int			j;

	j = 0;
	ft_setup_for_exec(command_list, &pfd, &npipes);
	while (command_list)
	{
		cmd = (t_command *)command_list->content;
		cmd->s = ft_builtin_cmd_found(cmd->str_tab_for_execve[0]);
		if (cmd->s >= 0 && cmd->s <= 6)
			cmd->exists = 1;
		if (cmd->exists == 1 && cmd->error == 0)
		{
			//ft_select_action(command_list, cmd, pfd, j);
			if (cmd->s >= 0 && cmd->s <= 3)
				ft_cmd_handler_no_fork(cmd, cmd->s);
			else
			{
				g_glob.fork_ret = fork();
				if (g_glob.fork_ret < 0)
					exit(EXIT_FAILURE);
				if (g_glob.fork_ret == 0)
				{
					ft_fds_and_pipes(command_list, cmd, pfd, j);
					ft_close_pipes(npipes, pfd);
					if (cmd->s >= 4 && cmd->s <= 6)
						ft_cmd_handler(cmd);
					else
					{
						if (cmd->error == 0)
						{
							if (execve(cmd->str_tab_for_execve[0],
									cmd->str_tab_for_execve, g_glob.env) == -1)
							{
								printf("minishell: %s\n", strerror(errno));
								exit(EXIT_FAILURE);
							}
						}
					}
				}
			}
		}
		else
		{
			if (cmd->error == 0)
				printf("minishell: %s: command not found\n",
					cmd->str_tab_for_execve[0]);
		}
		command_list = command_list->next;
		j += 2;
	}
	ft_parent_process(npipes, pfd);
}
