/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_role_macros_tab.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:00:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 14:13:38 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** void	ft_first_element_role(char **all_tab, int i, int *macros_array)
** This function is called when i = 0.
** The first element of the command is always either a redirection
** or a command itself (aka executable)
*/

static void	ft_first_element_role(char **all_tab, int i, int *macros_array)
{
	char	*current_element;

	current_element = all_tab[i];
	if (!ft_strlcmp(current_element, ">"))
		macros_array[i] = REDIR_R;
	else if (!ft_strlcmp(current_element, ">>"))
		macros_array[i] = REDIR_RR;
	else if (!ft_strlcmp(current_element, "<"))
		macros_array[i] = REDIR_L;
	else if (!ft_strlcmp(current_element, "<<"))
		macros_array[i] = REDIR_LL;
	else
		macros_array[i] = COMMAND;
}

static int	ft_determine_redirection(char **all_tab, int i)
{
	char	*current_element;

	current_element = all_tab[i];
	if (!ft_strlcmp(current_element, ">"))
		return (REDIR_R);
	else if (!ft_strlcmp(current_element, ">>"))
		return (REDIR_RR);
	else if (!ft_strlcmp(current_element, "<"))
		return (REDIR_L);
	else
		return (REDIR_LL);
}

static void	ft_determine_element_role(char **all, int i, int *t)
{
	int	l;

	l = ft_str_tab_len(all);
	if (!i)
		ft_first_element_role(all, i, t);
	else
	{
		// "echo > >" is a "syntax error near unexpected token '>'"!
		if (ft_str_is_a_redirection(all[i - 1]))
			t[i] = REDIR_ARG;
		else if (!ft_strlcmp(all[i], "|"))
			t[i] = PIPE;
		else if (ft_str_is_a_redirection(all[i]))
			t[i] = ft_determine_redirection(all, i);
		// if (we are after a redirection argument and we still have no command
		// ,this is the command
		else if (t[i - 1] == REDIR_ARG && !ft_elem_is_in_int_tab(t, l, COMMAND))
			t[i] = COMMAND;
		else if (t[i - 1] == REDIR_ARG && ft_elem_is_in_int_tab(t, l, COMMAND))
			t[i] = COMMAND_ARG;
		else if ((t[i - 1] == COMMAND || t[i - 1] == FLAG) && all[i][0] == '-')
			t[i] = FLAG;
		else if ((t[i - 1] == COMMAND || t[i - 1] == FLAG || t[i - 1] == COMMAND_ARG)
					&& all[i][0] != '-' && !ft_str_is_a_redirection(all[i]))
			t[i] = COMMAND_ARG;
		else
			t[i] = ERROR;
	}

}


void ft_extract_role_macros_tab(t_command *command)
{
	char	**all_tab;
	int		i;
	int		len;
	int		*macros_array;

	if (!command || !command->str_tab_all)
		return ;
	all_tab = command->str_tab_all;
	len = ft_str_tab_len(all_tab);
	command->role_macros = ft_calloc_exit(len, sizeof(int));
	macros_array = command->role_macros;
	i = -1;
	while (all_tab[++i])
	{
		ft_determine_element_role(all_tab, i, macros_array);
	}
}
