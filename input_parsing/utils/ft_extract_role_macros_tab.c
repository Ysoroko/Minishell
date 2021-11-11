/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_role_macros_tab.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:00:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/11 16:38:14 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** void	ft_first_element_role(char **all_tab, int i, int *macros_array)
** This function is called when i = 0.
** The first element of the command is always either a redirection, pipe
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
	else if (!ft_strlcmp(current_element, "|"))
		macros_array[i] = PIPE;
	else if (ft_role_macro_error(current_element))
		macros_array[i] = ERROR;
	else
		macros_array[i] = COMMAND;
}

static void	ft_after_redir_arg(char **all, int i, int *t, int l)
{
	if (!ft_elem_is_in_int_tab(t, l, COMMAND))
		t[i] = COMMAND;
	else if (ft_elem_is_in_int_tab(t, l, COMMAND)
		&& !ft_elem_is_in_int_tab(t, l, COMMAND_ARG)
		&& all[i][0] == '-' && ft_str_is_alpha_only(&(all[i][1])))
		t[i] = FLAG;
	else
		t[i] = COMMAND_ARG;
}

/*
** void	ft_based_on_previous_role(char **all, int i, int *t)
** This function determines the corresponding macro of the current
** element in "all" str array argument and sets the corresponding
** element in "t" int array to the corresponding macro value.
*/

static void	ft_based_on_previous_role(char **all, int i, int *t, int l)
{
	if (ft_str_is_a_redirection(all[i]))
		t[i] = ft_str_is_a_redirection(all[i]);
	else if (ft_role_macro_error(all[i]))
		t[i] = ERROR;
	else if (!ft_strlcmp(all[i], "|"))
		t[i] = PIPE;
	else if (ft_str_is_a_redirection(all[i - 1]))
		t[i] = REDIR_ARG;
	else if (t[i - 1] == REDIR_ARG)
		ft_after_redir_arg(all, i, t, l);
	else if ((t[i - 1] == COMMAND || t[i - 1] == FLAG) && all[i][0] == '-' &&
			ft_str_is_alpha_only((&(all[i][1]))))
		t[i] = FLAG;
	else if ((t[i - 1] == COMMAND || t[i - 1] == FLAG) && all[i][0] == '-' &&
			!ft_str_is_alpha_only((&(all[i][1]))))
		t[i] = COMMAND_ARG;
	else if ((t[i - 1] == COMMAND || t[i - 1] == FLAG) && all[i][0] != '-'
			&& !ft_str_is_a_redirection(all[i]))
		t[i] = COMMAND_ARG;
	else if (t[i - 1] == COMMAND_ARG)
		t[i] = COMMAND_ARG;
	else
		t[i] = ERROR;
}

/*
** void	ft_identify_redirection_arguments
** This function is used to determine precisely which redirection argument
** we have in front of us.
** Makes a distinction between "> >> < <<" and sets up the corresponding
** macros in the macros tab
*/

static void	ft_identify_redirection_arguments(int *macros_array, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (macros_array[i] == REDIR_ARG)
		{
			if (macros_array[i - 1] == REDIR_R)
				macros_array[i] = R_REDIR_ARG;
			else if (macros_array[i - 1] == REDIR_RR)
				macros_array[i] = RR_REDIR_ARG;
			else if (macros_array[i - 1] == REDIR_L)
				macros_array[i] = L_REDIR_ARG;
			else if (macros_array[i - 1] == REDIR_LL)
				macros_array[i] = LL_REDIR_ARG;
		}
	}
}

/*
** void	ft_extract_role_macros_tab(t_command *command)
** This function is responsible for creating the int array of macros
** based on the role of each element in "str_tab_all" in "command"
** argument
*/

void	ft_extract_role_macros_tab(t_command *command)
{
	char	**all_tab;
	int		i;
	int		len;
	int		*macros_array;

	if (!command || !command->str_tab_all)
		return ;
	all_tab = command->str_tab_all;
	len = ft_str_tab_len(all_tab);
	command->role_macros = ft_calloc_exit(len + 1, sizeof(int));
	macros_array = command->role_macros;
	i = -1;
	while (all_tab[++i])
	{
		if (!i)
			ft_first_element_role(all_tab, i, macros_array);
		else
			ft_based_on_previous_role(all_tab, i, macros_array, len);
	}
	ft_identify_redirection_arguments(macros_array, len);
}
