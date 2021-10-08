/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:22:37 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/08 14:12:38 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// This function will check the flag element in str_tab_all.
/// If it's "-n", it will modify the value of "end_of_line" character to '\0'
/// Otherwise, "end_of_line" will remain at '\n' and the value in role_macros
/// tab will be changed from "FLAG" to "COMMAND_ARG"
static void	ft_apply_n_flag(t_command *command, int i, char **end_of_line)
{
	char	*current_element;

	current_element = command->str_tab_all[i];
	if (!ft_strlcmp(current_element, "-n"))
		*end_of_line = '\0';
	else
		command->role_macros[i] = COMMAND_ARG;
}

/// This function will concatenate current element to *final_str string
/// if it's a command argument
/// If *final_str is NULL, we just duplicate the current element in str_tab_all
/// Otherwise, we join it to the previous value and free the old value
static void	ft_add_to_final_string(t_command *command, int i, char **final_str)
{
	char	*current_element;
	char	*temp;

	current_element = command->str_tab_all[i];
	if (!*final_str)
		*final_str = ft_strdup_exit(current_element);
	else
	{
		*final_str = ft_strjoin_free_pref_exit(final_str, " "); // lazy add space
		*final_str = ft_strjoin_free_pref_exit(final_str, current_element);
	}
}


void	ft_echo(t_command *command)
{
	int		i;
	char	*current_element;
	char	*final_str;
	char	end_of_line;

	end_of_line = '\n';
	i = -1;
	final_str = NULL;
	while (command->str_tab_all[++i])
	{
		current_element = command->str_tab_all[i];
		if (command->role_macros[i] == FLAG)
			ft_apply_n_flag(command, i, &end_of_line);
		if (command->role_macros[i] == COMMAND_ARG)
			ft_add_to_final_string(command, i, &final_str);
	}
	printf("%s%c", final_str, end_of_line);
}
