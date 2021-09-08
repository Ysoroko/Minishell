/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/08 12:34:03 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_EXECUTE
** This function is the main bridge between parsing and executing commands
** It takes the parsing as a t_list* structure, passes it to a different
** function which will execute all the commands for every element of 
** the t_list* structure
*/

void	ft_execute(t_dl_lst *command_list)
{
	if (!command_list)
		return ;
	ft_dl_lstiter(command_list, ft_print_command_list);
}
