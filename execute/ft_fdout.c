/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:18:43 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/20 09:26:34 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_fdout(t_command *cmd)
{
	cmd->error = 0;
	if (cmd->redir_type_out == REDIR_R)
		cmd->fdout = open(cmd->outfile, O_RDWR | O_TRUNC, 0664);
	else
		cmd->fdout = open(cmd->outfile, O_RDWR | O_APPEND, 0664);
	if (cmd->fdout == -1 && cmd->error == 0)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		ft_exit(errno);
	}
	if (dup2(cmd->fdout, 1) == -1 && cmd->error == 0)
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
