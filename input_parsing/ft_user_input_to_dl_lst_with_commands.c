/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_user_input_to_dl_lst_with_commands.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:35:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/11 16:33:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** void	ft_add_new_command_to_dl_lst(t_dl_lst *lst, t_command *new_command)
** This function will simply add the previously extracted t_command structure 
** "new_command" argument to already existing t_dl_lst structure "lst"
** containing all the commands of user's input
*/

static void	ft_add_new_command_to_dl_lst(t_dl_lst *lst, t_command *new_command)
{
	t_dl_lst	*new_list_member;

	if (!lst->content)
		lst->content = new_command;
	else
	{
		if (new_command->str_tab_all)
		{
			new_list_member = ft_dl_lst_new_exit((void *)new_command);
			ft_dl_lst_add_back(lst, new_list_member);
		}
	}
}

/*
** FT_INPUT_PARSING
** This is the central hub of the parsing of user's input
** It uses chained lists to divide input in several separated commands which
** will be read and executed afterwards
** Returns a chained list with pointers to each command's name / flags /
** arguments / redirections
*/

t_dl_lst	*ft_input_parsing(char *input, char *path)
{
	t_dl_lst	*command_list;
	int			i;
	t_command	*command;

	if (!input)
		return (0);
	command_list = ft_dl_lst_new_exit(0);
	i = -1;
	while (input[++i])
	{
		command = ft_extract_next_t_command(&input[i], &i);
		command->path = path;
		ft_add_new_command_to_dl_lst(command_list, command);
		if (!input[i])
			break ;
	}
	return (command_list);
}
