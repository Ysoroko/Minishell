/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_line_of_chars.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 15:00:34 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/25 15:05:36 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** void	ft_print_line_of_chars(char char_to_print, int len_of_the_line)
** This function is used to print a line of specified length composed
** only of "char_to_print" characters
** It is useful to print pretty lines of "_" character for debug functions
** and displayingarrays properly
*/

void	ft_print_line_of_chars(char char_to_print, int len_of_the_line)
{
	int	i;

	i = -1;
	while (++i < len_of_the_line)
		printf("%c", char_to_print);
	printf("\n");
}
