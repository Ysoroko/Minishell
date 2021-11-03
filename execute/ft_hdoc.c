/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:45:21 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/03 10:51:08 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_open_hdoc(t_command *cmd, int *fd)
{
	ft_open_hdoc_file(cmd, fd);
	g_glob.fork_ret = fork();
	if (g_glob.fork_ret < 0)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	else if (!g_glob.fork_ret)
		return (g_glob.fork_ret);
	else
		ft_wait_and_update_exit_status_hdoc();
	return (1);
}

void	ft_close_hdoc(t_command *cmd, int *fd)
{
	if (close(*fd) == -1)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
}

void	ft_add_redir_hdoc(t_command *cmd, int i)
{
	cmd->redir_type_in = 4;
	if (cmd->str_tab_all[i + 1] != NULL)
	{
		cmd->keyword[cmd->keyword_index] = ft_strdup(cmd->str_tab_all[i + 1]);
		if (cmd->keyword[cmd->keyword_index] == NULL)
		{
			ft_minishell_error(strerror(errno));
			ft_exit(errno);
		}
	}
	else
	{
		ft_minishell_error("syntax error");
		return ;
	}
	ft_heredoc_signals_setup();
	ft_hdoc(cmd);
	g_glob.fork_ret = 0;
	ft_setup_signals();
	cmd->keyword_index++;
	cmd->keyword[cmd->keyword_index] = 0;
}

void	ft_read_and_write_hdoc(t_command *cmd, int fd)
{
	if (cmd->buffer != NULL)
		free(cmd->buffer);
	cmd->buffer = readline("> ");
	if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) != 0)
		write(fd, cmd->buffer, ft_strlen(cmd->buffer));
	if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) != 0)
		write(fd, "\n", 1);
}

void	ft_hdoc(t_command *cmd)
{
	int	fd;

	if (ft_open_hdoc(cmd, &fd) == 0)
	{
		while (1)
		{
			ft_read_and_write_hdoc(cmd, fd);
			if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) == 0)
			{
				if (close(fd) == -1)
				{
					ft_minishell_error(strerror(errno));
					cmd->error = 1;
					ft_exit(errno);
				}
				exit(EXIT_SUCCESS);
				return ;
			}
		}
	}
	ft_close_hdoc(cmd, &fd);
}
