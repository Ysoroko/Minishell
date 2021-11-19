/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_command_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 15:56:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/19 13:36:45 by ysoroko          ###   ########.fr       */
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
	else if (m == REDIR_ARG || m == R_REDIR_ARG || m == RR_REDIR_ARG
		|| m == L_REDIR_ARG || m == LL_REDIR_ARG)
		return (BOLDBLUE);
	else if (m == PIPE)
		return (BOLDYELLOW);
	else
		return (BOLDRED);
}

/*
** char	*ft_role_str(int m)
** This function is used to determine the string for printing
** based on the corresponding value in macros_tab in our t_command structure
** Returns the corresponding string
*/

static char	*ft_role_str(int m)
{
	const char	*tab[] = {"ERROR", "REDIR_R", "REDIR_RR", "REDIR_L",
		"REDIR_LL", "REDIR_ARG", "PIPE", "COMMAND", "FLAG",
		"COMMAND_ARG", "R_REDIR_ARG", "L_REDIR_ARG",
		"RR_REDIR_ARG", "LL_REDIR_ARG"};

	if (m > ft_str_tab_len((char **)tab) || m < 0)
		return ("Undefined");
	else
		return ((char *)(tab[m]));
}

/*
** void	ft_print_tab_header(int	s)
** This function simply prints the header of the tab which will be like:
** ____________________________________________________________
** i        | Str_tab_all      | Macros tab       | Execve_tab 
** ____________________________________________________________
*/

static void	ft_print_tab_header(int s)
{
	printf(BOLDWHITE);
	ft_print_line_of_chars('_', LINE_LENGTH);
	printf("\n%*s | %*s | %*s | %*s\n", PLACE_FOR_I, "i", s, "str_tab_all", s,
		"role_macros", s, "str_tab_for_execve");
	ft_print_line_of_chars('_', LINE_LENGTH);
	printf("\n");
	printf(COLOR_RESET);
}

/*
** char	*ft_print_execve_tab(char **tab, int i)
** This function allows us to print execve_tab next to str_tab_all and macros
** despite execve_tab usually being shorter than those 2.
** It simply returns the execve_tab[i] element if element i exists
** or an empty string otherwise
*/

static char	*ft_print_execve_element(char **tab, int i)
{
	int	len;

	len = ft_str_tab_len(tab);
	if (i >= len)
		return ("");
	else
		return (tab[i]);
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

	s = -18;
	i = -1;
	printf("\n");
	command = (t_command *)(current_command);
	ft_print_tab_header(s);
	while (command->str_tab_all[++i])
	{
		str = (command->str_tab_all)[i];
		m = (command->role_macros)[i];
		printf("%*d | %*s | %s%*d: %*s%s | %*s\n", PLACE_FOR_I, i, s, str,
			ft_role_color(m), -2, m, s + 4, ft_role_str(m), COLOR_RESET, s,
			ft_print_execve_element(command->str_tab_for_execve, i));
	}
	ft_print_line_of_chars('_', LINE_LENGTH);
	printf("\n\n\n");
}
