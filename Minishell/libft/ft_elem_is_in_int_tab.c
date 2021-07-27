/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_is_in_int_tab.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 13:23:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 13:25:09 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** int	ft_elem_is_in_int_tab(int *tab, int tab_len, int elem)
** This function returns 1 if "elem" argument is present in the array of ints
** "tab" and returns 0 otherwise.
** If "tab" is a NULL pointer, returns 0
*/

int	ft_elem_is_in_int_tab(int *tab, int tab_len, int elem)
{
	int	i;

	i = -1;
	if (!tab)
		return (0);
	while (++i < tab_len)
	{
		if (tab[i] == elem)
			return (1);
	}
	return (0);
}
