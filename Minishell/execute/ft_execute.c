/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/07 15:28:08 by ysoroko          ###   ########.fr       */
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
		{
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
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
		{
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_fdin(t_command *cmd)
{
	cmd->error = 0;
	if (cmd->redir_type_in == REDIR_L)
		cmd->fdin = open(cmd->infile, O_RDONLY);
	else
		cmd->fdin = open("hdoc/tmp", O_RDONLY);
	if (cmd->fdin == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
	if (dup2(cmd->fdin, 0) == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
	if (close(cmd->fdin) == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
}

void	ft_fdout(t_command *cmd)
{
	cmd->error = 0;
	if (cmd->redir_type_out == REDIR_R)
		cmd->fdout = open(cmd->outfile, O_RDWR | O_TRUNC, 0664);
	else
		cmd->fdout = open(cmd->outfile, O_RDWR | O_APPEND, 0664);
	if (cmd->fdout == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
	if (dup2(cmd->fdout, 1) == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
	if (close(cmd->fdout) == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
}

void	ft_pipe_cmd(t_dl_lst *command_list, t_command *cmd, int *pfd, int j)
{
	if (command_list->next)
		if (cmd->redir_type_out != REDIR_R || cmd->redir_type_out != REDIR_RR)
			if (dup2(pfd[j + 1], 1) == -1)
			{
				printf("%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
	if (j != 0)
		if (cmd->redir_type_in != REDIR_L || cmd->redir_type_in != REDIR_LL)
			if (dup2(pfd[j - 2], 0) == -1)
			{
				printf("%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
}

void	ft_setup_for_exec(t_dl_lst *lst, int **pfd, int *npipes)
{
	*npipes = ft_lstsize((t_list *)lst) - 1;
	*pfd = (int *)malloc(sizeof(int) * (*npipes * 2));
	if (!(*pfd))
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
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

int	ft_builtin_cmd_found(char *exec_name)
{
	if (ft_strcmp("/bin/echo", exec_name) == 0)
		return (1);
	if (ft_strcmp("/usr/bin/cd", exec_name) == 0)
		return (2);
	if (ft_strcmp("/bin/pwd", exec_name) == 0)
		return (3);
	if (ft_strcmp("export", exec_name) == 0)
		return (4);
	if (ft_strcmp("unset", exec_name) == 0)
		return (5);
	if (ft_strcmp("/usr/bin/env", exec_name) == 0)
		return (6);
	if (ft_strcmp("exit", exec_name) == 0)
		return (7);
	return (0);
}

char	*ft_getenv(char *s)
{
	if (ft_env_index >= 0)
		return (g_glob.env[ft_env_index(s)] + (ft_strlen(s) + 1));
	return (NULL);
}

void	ft_export_handler(t_command *cmd)
{
	int	i;
	char	**tmp;

	i = 1;
	tmp = g_glob.env;
	while (cmd->str_tab_for_execve[i])
	{
		if (ft_env_index(cmd->str_tab_for_execve[i]) >= 0)
		{
			g_glob.env = ft_unset(cmd->str_tab_for_execve[i]);
			g_glob.env = ft_export(cmd->str_tab_for_execve[i]);
		}
		else
			g_glob.env = ft_export(cmd->str_tab_for_execve[i]);
		i++;
	}
}

void	ft_unset_handler(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->str_tab_for_execve[i])
	{
		if (ft_env_index(cmd->str_tab_for_execve[i]) >= 0)
			g_glob.env = ft_unset(cmd->str_tab_for_execve[i]);
		i++;
	}
}

int	ft_builtin_cmd_handler(t_command *cmd)
{
	int x;

	x = ft_builtin_cmd_found(cmd->str_tab_for_execve[0]);
	if (x == 1)
		ft_echo(cmd);
	if (x == 2)
		ft_cd(cmd->str_tab_for_execve[1]);
	if (x == 3)
		ft_pwd(cmd);
	if (x == 4)
		ft_export_handler(cmd);
	if (x == 5)
		ft_unset_handler(cmd);
	if (x == 6)
		ft_env();
	if (x == 7)
		ft_exit();
	return (0);
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
		if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) > 0)
			ft_builtin_cmd_handler(cmd);
		else
		{
			if (cmd->exists == 1 && cmd->error == 0)
			{
				g_glob.fork_ret = fork();
				if (g_glob.fork_ret < 0)
					exit(EXIT_FAILURE);
				if (g_glob.fork_ret == 0)
				{
					ft_fds_and_pipes(command_list, cmd, pfd, j);
					ft_close_pipes(npipes, pfd);
					if (cmd->error == 0)
					{
						if (execve(cmd->str_tab_for_execve[0], cmd->str_tab_for_execve, g_glob.env) == -1)
						{
							printf("%s\n", strerror(errno));
							exit(EXIT_FAILURE);
						}
					}
				}
			}
		}
		command_list = command_list->next;
		j += 2;
	}
	ft_parent_process(npipes, pfd);
}
