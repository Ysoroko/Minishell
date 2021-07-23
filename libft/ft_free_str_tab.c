/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 12:22:41 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/23 12:26:36 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** void	*ft_free_str_tab(char ***str_tab, void *to_return)
** This function is used to free str_tab argument, an array of strings ending
** by a NULL pointer.
** Returns to_return argument;
*/

void	*ft_free_str_tab(char ***str_tab, void *to_return)
{
	int	i;

	if (!str_tab || !*str_tab)
		return (to_return);
	i = -1;
	while ((*str_tab)[++i])
		free((*str_tab)[i]);
	free(*str_tab);
	return (to_return);
}
