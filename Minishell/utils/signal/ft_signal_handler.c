/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:36:31 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/06 11:37:26 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** FT_SIGNAL_HANDLER
** This function will be called in our "signal()" function to intercept the
** CTRL+C signal and instead of quitting our minishell we will just execute
** this function
** As per "signal()" function this function needs to be of a prototype
** "void ft(int n)", but in this case we don't need the int parameter
*/

void	ft_signal_handler(int no_matter)
{
	printf(BOLDRED);
	printf("\n\nCiao! 👋\n");
	printf(COLOR_RESET);
	no_matter += 1;
	exit(EXIT_SUCCESS);
}
