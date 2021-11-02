/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_nq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:00:16 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/22 16:50:33 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_STRCHR_NQ
** Same as ft_strchr, but only considers a character to be found if it's not
** between two quotes
*/

char	*ft_strchr_nq(const char *str_with_c, int c_pos, char *sep)
{
	int		i;
	char	to_look;
	char	*my_str;

	my_str = (char *)(str_with_c);
	to_look = str_with_c[c_pos];
	i = 0;
	while (sep[i])
	{
		if (sep[i] == to_look && !ft_char_between_the_quotes(c_pos, my_str))
			return (&(sep[i]));
		i++;
	}
	if (sep[i] == to_look)
		return (&(sep[i]));
	return (0);
}
