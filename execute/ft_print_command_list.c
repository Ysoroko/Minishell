/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_command_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:41:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 14:45:01 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** char	*ft_role_color(int m)
** This function is used to determine the color for printing
** based on the corresponding value in macros_tab in our t_command structure
** Returns the string containing the color
*/

static char	*ft_role_color(int m)
{
	if (m == ERROR)
		return (BOLDRED);
	else if (m == COMMAND)
		return (BOLDGREEN);
	else if (m == FLAG)
		return (BOLDWHITE);
	else if (m == COMMAND_ARG)
		return (BOLDCYAN);
	else if (m == REDIR_L || m == REDIR_LL || m == REDIR_R || m == REDIR_RR)
		return (BOLDMAGENTA);
	else if (m == REDIR_ARG)
		return (BOLDBLUE);
	else if (m == PIPE)
		return (BOLDYELLOW);
	else
		return (COLOR_RESET);
}

/*
** char	*ft_role_str(int m)
** This function is used to determine the string for printing
** based on the corresponding value in macros_tab in our t_command structure
** Returns the corresponding string
*/

static char	*ft_role_str(int m)
{
	if (m == ERROR)
		return ("Error");
	else if (m == COMMAND)
		return ("Command");
	else if (m == FLAG)
		return ("Flag");
	else if (m == COMMAND_ARG)
		return ("Command argument");
	else if (m == REDIR_L)
		return ("<");
	else if (m == REDIR_LL)
		return ("<<");
	else if (m == REDIR_R)
		return (">");
	else if (m == REDIR_RR)
		return (">>");
	else if (m == PIPE)
		return ("Pipe");
	else if (m == REDIR_ARG)
		return ("Redirection argument");
	else
		return ("Undefined role");
}

static void	ft_print_tab_header(int	s)
{
	printf(BOLDWHITE);
	printf("____________________________________________________________\n\n");
	printf("%*s | %*s | %*s\n", -8, "i", s, "Str_tab_all", s, "Macros tab");
	printf("____________________________________________________________\n\n");
	printf(COLOR_RESET);
}

/*
** FT_PRINT_COMMAND_LIST
** A debugging function used to print the list of our commands and related
** flags/arguments/redirections to make sure everything is running smoothly
*/

void	ft_print_command_list(void *current_command)
{
	t_command	*command;
	int			s;
	char		*str;
	int			m;
	int			i;

	s = -16;
	i = -1;
	printf("\n");
	command = (t_command *)(current_command);
	ft_print_tab_header(s);
	while (command->str_tab_all[++i])
	{
		str = (command->str_tab_all)[i];
		m = (command->role_macros)[i];
		printf("%*d | %*s | %s%*s%s\n", -8, i, s, str, ft_role_color(m),
			s, ft_role_str(m), COLOR_RESET);
	}
	printf("____________________________________________________________\n\n");
	printf("%*s\n", s, "Str_tab_for execve:");
	ft_putstr_tab(command->str_tab_for_execve, STDOUT);
	printf("____________________________________________________________\n\n");
}
