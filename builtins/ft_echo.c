/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:22:37 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/28 16:55:08 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// This function will concatenate current element to *final_str string
/// if it's a command argument
/// If *final_str is NULL, we just duplicate the current element in str_tab_all
/// Otherwise, we join it to the previous value and free the old value
static void	ft_add_to_final_string(char *current_element, char **final_str)
{
	if (!*final_str)
		*final_str = ft_strdup_exit(current_element);
	else
	{
		*final_str = ft_strjoin_free_pref_exit(final_str, " ");
		*final_str = ft_strjoin_free_pref_exit(final_str, current_element);
	}
}

void	ft_echo(char **str_tab_for_execve)
{
	int		i;
	char	*current_element;
	char	*final_str;
	char	end_of_line;

	end_of_line = '\n';
	i = 0;
	final_str = 0;
	while (str_tab_for_execve[++i])
	{
		current_element = str_tab_for_execve[i];
		if (i == 1 && !ft_strlcmp(current_element, "-n"))
			end_of_line = '\0';
		else
			ft_add_to_final_string(current_element, &final_str);
	}
	printf("%s%c", final_str, end_of_line);
	free(final_str);
}

int	main(int argc, char **str_tab_for_execve, char **env)
{
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	else if (argc == 2 && !(ft_strlcmp(str_tab_for_execve[1], "-n")))
	{
		printf("");
		return (0);
	}
	g_glob.env = env;
	ft_echo(str_tab_for_execve);
	return (0);
}