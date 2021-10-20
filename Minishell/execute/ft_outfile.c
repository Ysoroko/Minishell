/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:49:19 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/20 06:19:04 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_copy_outfile(t_command *cmd, int i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->str_tab_all[i + 1] != NULL)
	{
		cmd->outfile = ft_strdup(cmd->str_tab_all[i + 1]);
		if (cmd->outfile == NULL)
		{
			ft_minishell_error(strerror(errno));
			ft_exit(errno);
		}
	}
	else
	{
		ft_minishell_error("syntax error");
		ft_exit(errno);
	}
}

void	ft_add_redir_out(t_command *cmd, int m, int i)
{
	ft_copy_outfile(cmd, i);
	if (m == REDIR_R)
	{
		cmd->fdout = open(cmd->outfile, O_CREAT | O_TRUNC, 0664);
		cmd->redir_type_out = 1;
	}
	else if (m == REDIR_RR)
	{
		cmd->fdout = open(cmd->outfile, O_CREAT | O_APPEND, 0664);
		cmd->redir_type_out = 2;
	}
	if (cmd->fdout == -1 && cmd->error == 0)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
	if (close(cmd->fdout) == -1 && cmd->error == 0)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
}
