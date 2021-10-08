/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:18:03 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 07:18:26 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
