/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ressources.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 08:01:05 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/15 08:04:24 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_ressources(t_command *cmd)
{
	if (cmd->infile != NULL)
		free(cmd->infile);
	if (cmd->outfile != NULL)
		free(cmd->outfile);
	if (cmd->buffer != NULL)
		free(cmd->buffer);
	if (cmd->keyword_index)
	{
		while (cmd->keyword_index >= 0)
		{
			if (cmd->keyword[cmd->keyword_index] != NULL)
				free(cmd->keyword[cmd->keyword_index]);
			cmd->keyword_index--;
		}
	}
	free(cmd->keyword);
}
