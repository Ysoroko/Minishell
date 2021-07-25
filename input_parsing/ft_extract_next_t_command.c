/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_t_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 12:59:14 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_EXTRACT_NEXT_COMMAND
** This function will first extract the string representing the next command
** (commands are divided by '|' symbol in Minishell project)
** It will then analyze this command and extract all the necessary information
** from it like what is redirection, what is an argument and so on.
** Returns a t_command structure will all the necessary information.
*/

t_command	*ft_extract_next_t_command(char *input_checkpt, int *i)
{
	int			j;
	t_command	*command;
	char		*next_command_as_str;

	command = ft_calloc_exit(1, sizeof(t_command));
	next_command_as_str = ft_extract_next_command_string(input_checkpt);
	j = ft_strlen(next_command_as_str);
	ft_extract_str_tab_all(next_command_as_str, command);
	ft_extract_str_tab_for_execve(command);
	ft_free_str(&next_command_as_str);
	if (!j)
		*i += 1;
	*i += j - 1;
	return (command);
}
