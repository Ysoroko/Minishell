/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha_only.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:40:52 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/26 15:12:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** int	ft_str_is_alpha_only(char *str)
** This function will return 1 if "str" string argument is only composed
** of alphabetic characters.
** Returns 0 otherwise (or if str is a NULL pointer)
*/

int	ft_str_is_alpha_only(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = -1;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
	}
	return (1);
}
