/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_map_single_dstr_arg.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:37:37 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/26 12:47:06 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** char	**ft_strtab_map_str_dstr_arg(char **st, char *f(char **))
** This function will apply argument function "f" tp every string in **str_tab
** argument and return a new, malloc'd str_tab.
** If a malloc call fails inside, it will call exit(EXIT_FAILURE) function.
** Returns the new version of str_tab (the old one still needs to be freed
** if malloc'd).
*/

char	**ft_strtab_map_single_dstr_arg(char **st, char *f(char **))
{
	char			**ret_str_tab;
	unsigned int	i;
	int				len;

	if (!st || !f)
		return (0);
	i = -1;
	len = ft_str_tab_len(st);
	ret_str_tab = ft_calloc_exit(len + 1, sizeof(*st));
	while (st[++i])
		ret_str_tab[i] = f(&(st[i]));
	return (ret_str_tab);
}
