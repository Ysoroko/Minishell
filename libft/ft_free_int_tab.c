/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 12:13:06 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 12:14:08 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** void	*ft_free_int_tab(int **int_tab, void *to_return)
** This function is used to free int_tab argument, an array of ints
** Returns to_return argument;
*/

void	*ft_free_int_tab(int **int_tab, void *to_return)
{
	if (!int_tab || !*int_tab)
		return (to_return);
	free(*int_tab);
	return (to_return);
}
