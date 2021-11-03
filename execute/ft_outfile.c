/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:49:19 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/03 13:53:22 by ysoroko          ###   ########.fr       */
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
		ft_err(NULL, NULL, "syntax error", 258);
		return ;
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
		ft_err(NULL, NULL, strerror(errno), 1);
		cmd->error = 1;
	}
	if (close(cmd->fdout) == -1 && cmd->error == 0)
		cmd->error = 1;
}
