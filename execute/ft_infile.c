/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:47:21 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/03 13:53:05 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_copy_infile(t_command *cmd, int i)
{
	cmd->redir_type_in = 3;
	cmd->error = 0;
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->str_tab_all[i + 1] != NULL)
	{
		cmd->infile = ft_strdup_exit(cmd->str_tab_all[i + 1]);
		if (cmd->infile == NULL)
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

void	ft_add_redir_in(t_command *cmd, int i)
{
	ft_copy_infile(cmd, i);
	cmd->fdin = open(cmd->infile, O_RDONLY);
	if (cmd->fdin == -1 && cmd->error == 0)
	{
		cmd->error = 1;
		ft_err(NULL, NULL, strerror(errno), 1);
	}
	if (close(cmd->fdin) == -1 && cmd->error == 0)
		cmd->error = 1;
}
