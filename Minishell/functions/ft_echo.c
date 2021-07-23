/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:11:16 by ysoroko           #+#    #+#             */
/*   Updated: 2021/05/06 12:04:32 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** ft_echo
** This is the function resposible for reproducing "echo" bash command
** Echo bash command simply displays its arguments separated by spaces 
** with a newline '\n' char at the end
** If "-n" flag is present, it doesn't add the end of line '\n' char at the end
** Echo doesn't do anything with redirecting input '<'
** but works as usual with '>' and '>>'
*/

void	ft_echo(t_dl_lst *dl_lst, int output_fd)
{
	t_command	*current_command;

	current_command = (t_command *)(dl_lst->content);
	if (current_command->flags)
		ft_putstr_fd(current_command->argument, output_fd);
	else
		ft_putendl_fd(current_command->argument, output_fd);
}
