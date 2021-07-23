/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_map_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:57:41 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/23 12:28:21 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** char	*ft_strtab_map(char **str_tab, char (*f)(char *))
** This function will apply argument function "f" tp every string in **str_tab
** argument and return a new, malloc'd str_tab.
** If a malloc call fails inside, it will call exit(EXIT_FAILURE) function.
** Returns the new version of str_tab (the old one still needs to be freed
** if malloc'd).
*/

char	**ft_strtab_map_exit(char **stab, char (*f)(char *, char *), char *arg)
{
	char			**ret_str_tab;
	unsigned int	i;
	int				len;

	if (!stab || !f)
		return (0);
	i = -1;
	len = ft_str_tab_len(stab);
	ret_str_tab = ft_calloc_exit(len + 1, sizeof(*stab));
	while (stab[++i])
		ret_str_tab[i] = f(stab[i], arg);
	return (ret_str_tab);
}
