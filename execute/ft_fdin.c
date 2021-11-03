/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:18:03 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/03 17:29:54 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_open_fdins(t_command *cmd)
{
	char	*str;

	str = ft_strjoin_exit(cmd->path, "tmp");
	if (cmd->redir_type_in == REDIR_L)
		cmd->fdin = open(cmd->infile, O_RDONLY);
	else
		cmd->fdin = open(str, O_RDONLY);
	free(str);
	if (cmd->fdin == -1 && cmd->error == 0)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
}

void	ft_fdin(t_command *cmd)
{
	cmd->error = 0;
	ft_open_fdins(cmd);
	if (dup2(cmd->fdin, 0) == -1 && cmd->error == 0)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
	if (close(cmd->fdin) == -1 && cmd->error == 0)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
}
