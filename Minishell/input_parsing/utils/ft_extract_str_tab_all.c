/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_str_tab_all.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 12:43:22 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/26 12:47:32 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	ft_extract_str_tab_all(char *next_command_str, t_command *command)
{
	char	**temp;
	char	**temp2;

	if (!command || !next_command_str)
		return ;
	temp = ft_split_seps_included_exit(next_command_str, SPACES_REDIRS_PIPES);
	temp2 = ft_strtab_map_str_exit(temp, ft_strtrim_exit, SPACES);
	command->str_tab_all = ft_copy_str_tab_except_for(temp2, SPACES);
	ft_free_str_tab(&temp, 0);
	ft_free_str_tab(&temp2, 0);
}
