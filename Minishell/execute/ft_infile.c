/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:47:21 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 06:47:43 by ablondel         ###   ########.fr       */
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
		cmd->infile = ft_strdup(cmd->str_tab_all[i + 1]);
		if (cmd->infile == NULL)
		{
			printf("%s\n", strerror(ENOMEM));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("minishell: syntax error\n");
		exit(EXIT_FAILURE);
	}
}

void	ft_add_redir_in(t_command *cmd, int m, int i)
{
	ft_copy_infile(cmd, i);
	cmd->fdin = open(cmd->infile, O_RDONLY);
	if (cmd->fdin == -1 && cmd->error == 0)
	{
		printf("minishell: %s: %s\n", cmd->infile, strerror(errno));
		cmd->error = 1;
	}
	if (close(cmd->fdin) == -1 && cmd->error == 0)
	{
		printf("%s\n", strerror(errno));
		cmd->error = 1;
	}
}
