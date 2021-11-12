/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_t_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/12 15:03:28 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**ft_quotes_env_variables_and_update_macros(t_command *command)
{
	char	**str_tab_all;
	int		*macros_tab;
	char	**temp;
	int		p_m;
	int		i;

	str_tab_all = command->str_tab_all;
	macros_tab = command->role_macros;
	i = ft_str_tab_len(str_tab_all);
	temp = ft_calloc_exit(i + 1, sizeof(*str_tab_all));
	i = -1;
	while (str_tab_all[++i])
	{
		temp[i] = ft_apply_quotes_and_env_vars(&(str_tab_all[i]));
		if (i && temp[i][0] == '-' && ft_str_is_alpha_only(&(temp[i][1])))
		{
			p_m = macros_tab[i - 1];
			if ((p_m == COMMAND || ft_is_a_redir_arg_macro(p_m) || p_m == FLAG)
				&& !ft_elem_is_in_int_tab(macros_tab, i - 1, COMMAND_ARG))
			{
				macros_tab[i] = FLAG;
			}
		}
	}
	return ((char **)(ft_free_str_tab(&str_tab_all, temp)));
}

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
	char		*temp;

	command = ft_calloc_exit(1, sizeof(t_command));
	next_command_as_str = ft_extract_next_command_string(input_checkpt);
	temp = ft_apply_env_vars(&next_command_as_str);
	j = ft_strlen(next_command_as_str);
	ft_extract_str_tab_all(temp, command);
	ft_extract_role_macros_tab(command);
	command->str_tab_all = ft_quotes_env_variables_and_update_macros(command);
	ft_extract_str_tab_for_execve(command);
	ft_free_str(&next_command_as_str);
	ft_free_str(&temp);
	if (!j)
		*i += 1;
	*i += j - 1;
	return (command);
}
