/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/08 04:36:54 by ablondel         ###   ########.fr       */
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
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->infile)
		free(cmd->infile);
	ft_pipe_cmd(lst, cmd, pfd, j);
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

int	ft_builtin_cmd_found(char *exec_name)
{
	if (ft_strcmp("/usr/bin/cd", exec_name) == 0)
		return (0);
	if (ft_strcmp("export", exec_name) == 0)
		return (1);
	if (ft_strcmp("unset", exec_name) == 0)
		return (2);
	if (ft_strcmp("exit", exec_name) == 0)
		return (3);
	if (ft_strcmp("/bin/echo", exec_name) == 0)
		return (4);
	if (ft_strcmp("/bin/pwd", exec_name) == 0)
		return (5);
	if (ft_strcmp("/usr/bin/env", exec_name) == 0)
		return (6);
	return (-1);
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

	i = 1;
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

int	ft_cmd_handler(t_command *cmd)
{
	char	*tmp;

	tmp = cmd->str_tab_for_execve[0];
	if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 4)
		cmd->str_tab_for_execve[0] = ft_strjoin_exit(g_glob.origin, "./ft_echo");
	if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 5)
		cmd->str_tab_for_execve[0] = ft_strjoin_exit(g_glob.origin, "./ft_pwd");
	if (ft_builtin_cmd_found(cmd->str_tab_for_execve[0]) == 6)
		cmd->str_tab_for_execve[0] = ft_strjoin_exit(g_glob.origin, "./ft_env");
	free(tmp);
	if (execve(cmd->str_tab_for_execve[0], cmd->str_tab_for_execve, g_glob.env) == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (-1);
}

void	ft_cmd_handler_no_fork(t_command *cmd, int s)
{
	if (s == 0)
		if (chdir(cmd->str_tab_for_execve[1]) == -1)
			printf("minishell: cd: %s: %s\n", cmd->str_tab_for_execve[1], strerror(errno));
	if (s == 1)
		ft_export_handler(cmd);
	if (s == 2)
		ft_unset_handler(cmd);
	if (s == 3)
		ft_exit();
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
			if (execve(cmd->str_tab_for_execve[0], cmd->str_tab_for_execve, g_glob.env) == -1)
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
			ft_child_process(lst, cmd, pfd, j);
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
			ft_select_action(command_list, cmd, pfd, j);
		else
			printf("minishell: %s: command not found\n",
			cmd->str_tab_for_execve[0]);
		command_list = command_list->next;
		j += 2;
	}
	ft_parent_process(npipes, pfd);
}
