/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_str_tab_for_execve.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 12:48:40 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 13:02:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** int	ft_str_tab_len_for_execve(char **s_tab)
** This function calculates the number of elements we need for the 
** str_tab_for_execve string array in t_command structure.
** We do not count redirections and redirection arguments which will not
** be present in str_tab_for_execve.
** Returns the number of strings necessary.
*/

static int	ft_str_tab_len_for_execve(char **s_tab)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s_tab[++i])
	{
		if (!ft_str_only_has_chars_from_charset(s_tab[i], REDIRS_AND_PIPES))
		{
			if (i && !ft_str_only_has_chars_from_charset(s_tab[i - 1],
					REDIRS_AND_PIPES))
				count++;
			else if (!i)
				count++;
		}
	}
	return (count);
}

/*
** char	**ft_copy_str_tab_for_execve(char **s_tab)
** This function is responsible for copying the str_tab_all
** to str_tab_for_execve.
** It will not copy redirections and redirection arguments.
** Returns the result string array.
*/

static char	**ft_copy_str_tab_for_execve(char **s_tab)
{
	char	**ret;
	int		i;
	int		len;
	int		j;

	len = ft_str_tab_len_for_execve(s_tab);
	ret = ft_calloc_exit(len + 1, sizeof(*s_tab));
	i = -1;
	j = -1;
	while (s_tab[++i])
	{
		if (!ft_str_only_has_chars_from_charset(s_tab[i], REDIRS_AND_PIPES))
		{
			if (i && !ft_str_only_has_chars_from_charset(s_tab[i - 1],
					REDIRS_AND_PIPES))
				ret[++j] = ft_strdup_exit(s_tab[i]);
			else if (!i)
				ret[++j] = ft_strdup_exit(s_tab[i]);
		}
	}
	return (ret);
}

/*
** ft_extract_str_tab_for_execve(char *command_as_str, t_command *command)
** This function fills in the "str_tab_for_execve" fiels in t_command
** structure.
** It uses str_tab_all from the same structure, but does not copy
** redirections and redirection arguments inside the final string array
*/

void	ft_extract_str_tab_for_execve(t_command *command)
{
	char	**base;

	if (!command)
		return ;
	base = command->str_tab_all;
	command->str_tab_for_execve = ft_copy_str_tab_for_execve(base);
}
