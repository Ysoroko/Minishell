/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:22:37 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/15 17:28:27 by ysoroko          ###   ########.fr       */
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

static int	ft_is_a_flag_argument(char *str, int flagged)
{
	if (str[0] == '-' && ft_str_only_has_chars_from_charset(&str[1], "n")
		&& flagged == 0)
	{
		return (1);
	}
	return (0);
}

void	ft_echo(char **str_tab_for_execve)
{
	int		i;
	int		flagged;
	char	*str;
	char	*final_str;
	char	end_of_line;

	end_of_line = '\n';
	i = 0;
	flagged = 0;
	final_str = NULL;
	while (str_tab_for_execve[++i])
	{
		str = str_tab_for_execve[i];
		if (ft_is_a_flag_argument(str, flagged))
			end_of_line = '\0';
		else
		{
			flagged = 1;
			ft_add_to_final_string(str, &final_str);
		}
	}
	if (!final_str)
		final_str = ft_strdup_exit("");
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
