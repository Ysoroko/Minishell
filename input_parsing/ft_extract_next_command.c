/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_next_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:52:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/23 14:21:56 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static char **ft_copy_str_tab_except_for(char **str_tab, char *except)
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
** This function analyzes the input read so far and stores it in a t_command
** It is a central hub of a transformation from input read into one separate
** t_command structure
*/

t_command	*ft_extract_next_command(char *input_checkpt, int *i)
{
	int			j;
	t_command	*command;
	char		*next_command_as_str;
	char		**temp_str_tab;
	char		**temp_str_tab2;

	command = ft_calloc_exit(1, sizeof(t_command));
	next_command_as_str = ft_extract_next_command_string(input_checkpt);
	j = ft_strlen(next_command_as_str);
	temp_str_tab = ft_split_seps_included_exit(next_command_as_str, SPACES_REDIRS_PIPES);
	printf("after split: \n");
	ft_putstr_tab(temp_str_tab, STDOUT);
	temp_str_tab2 = ft_strtab_map_str_exit(temp_str_tab, ft_strtrim_exit, SPACES);
	printf("after map: \n");
	ft_putstr_tab(temp_str_tab2, STDOUT);
	ft_free_str_tab(&temp_str_tab, 0);
	command->str_tab_all = ft_copy_str_tab_except_for(temp_str_tab2, SPACES);
	ft_free_str_tab(&temp_str_tab2, 0);
	ft_free_str(&next_command_as_str);
	if (!j)
		*i += 1;
	*i += j - 1;
	return (command);
}

// divide the command in redirections
// 1) check if there is a redirection
// 		if no -> first word is a command's name, next are its arguments
// 		if yes -> first word is a redir arg file, next is command name or its arguments
// 2) What redirection it is? Modify command's final stdin/stdout
