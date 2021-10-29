/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:45:21 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/29 15:48:02 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_open_hdoc(t_command *cmd, int *fd)
{
	int	forked;

	if (ft_check_file_permissions("hdoc/tmp") >= 1)
		*fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	else
		*fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (*fd == -1)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
	forked = fork();
	if (forked < 0)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	else if (!forked)
		return (forked);
	else
		wait(NULL);
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
	ft_hdoc(cmd);
	cmd->keyword_index++;
	cmd->keyword[cmd->keyword_index] = 0;
}

void	ft_hdoc(t_command *cmd)
{
	int	fd;

	if (ft_open_hdoc(cmd, &fd) == 0)
	{
		while (1)
		{
			if (cmd->buffer != NULL)
				free(cmd->buffer);
			cmd->buffer = readline("> ");
			if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) != 0)
				write(fd, cmd->buffer, ft_strlen(cmd->buffer));
			if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) != 0)
				write(fd, "\n", 1);
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
