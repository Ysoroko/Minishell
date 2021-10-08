/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:45:21 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 06:46:32 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_open_hdoc(t_command *cmd, int *fd)
{
	if (ft_check_file_permissions("hdoc/tmp") >= 1)
		*fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	else
		*fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (*fd == -1)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
}

void	ft_close_hdoc(t_command *cmd, int *fd)
{
	if (close(*fd) == -1)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
		exit(EXIT_FAILURE);
	}
}

void	ft_add_redir_hdoc(t_command *cmd, int m, int i)
{
	cmd->redir_type_in = 4;
	if (cmd->str_tab_all[i + 1] != NULL)
	{
		cmd->keyword[cmd->keyword_index] = ft_strdup(cmd->str_tab_all[i + 1]);
		if (cmd->keyword[cmd->keyword_index] == NULL)
		{
			printf("%s\n", strerror(ENOMEM));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("minishell: syntax error near unexpected token\n");
		exit(EXIT_FAILURE);
	}
	ft_hdoc(cmd);
	cmd->keyword_index++;
	cmd->keyword[cmd->keyword_index] = 0;
}

void	ft_hdoc(t_command *cmd)
{
	int	fd;

	ft_open_hdoc(cmd, &fd);
	while (1)
	{
		cmd->buffer = readline("> ");
		write(fd, cmd->buffer, ft_strlen(cmd->buffer));
		if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) != 0)
			write(fd, "\n", 1);
		if (cmd->buffer != NULL)
			free(cmd->buffer);
		if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) == 0)
		{
			ft_close_hdoc(cmd, &fd);
			return ;
		}
	}
	ft_close_hdoc(cmd, &fd);
}
