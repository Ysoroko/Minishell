/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_t_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/26 16:22:59 by ysoroko          ###   ########.fr       */
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
	;
	return ((char **)(ft_free_str_tab(&str_tab_all, temp)));
}

/*
** int	ft_str_tab_len_without_str_with_only_excl(char **s_tab, char *excl)
** This function is used to count the length of str_tab needed to malloc.
** It doesn't count the words in s_tab composed solely of characters
** present in *excl argument.
** In minishell it's used to avoid counting strings composed only of spaces
*/

static int	ft_str_tab_len_without_str_with_only_excl(char **s_tab, char *excl)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s_tab[++i])
	{
		if (!ft_str_only_has_chars_from_charset(s_tab[i], excl))
			count++;
	}
	return (count);
}

/*
** char **ft_copy_str_tab_except_for(char **str_tab, char *except)
** This function is used to copy **str_tab but not copy
** strings composed only of characters present in *except argument
** In minishell, this is used to avoid copying strings composed
** only of spaces.
*/

static char	**ft_copy_str_tab_except_for(char **str_tab, char *except)
{
	char	**ret;
	int		len;
	int		i;
	int		j;

	len = ft_str_tab_len_without_str_with_only_excl(str_tab, except);
	ret = ft_calloc_exit(len + 1, sizeof(*str_tab));
	i = -1;
	j = -1;
	while (str_tab[++i])
	{
		if (!ft_str_only_has_chars_from_charset(str_tab[i], except))
			ret[++j] = ft_strdup_exit(str_tab[i]);
	}
	return (ret);
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
	char		**temp;

	command = ft_calloc_exit(1, sizeof(t_command));
	next_command_as_str = ft_extract_next_command_string(input_checkpt);
	j = ft_strlen(next_command_as_str);
	ft_extract_str_tab_all(next_command_as_str, command);
	ft_extract_role_macros_tab(command);
	temp = ft_quotes_env_variables_and_update_macros(command);
	command->str_tab_all = ft_copy_str_tab_except_for(temp, SPACES);
	ft_extract_str_tab_for_execve(command);
	ft_free_str_tab(&temp, 0);
	ft_free_str(&next_command_as_str);
	if (!j)
		*i += 1;
	*i += j - 1;
	return (command);
}
