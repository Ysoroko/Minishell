/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:36:31 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/24 12:09:30 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_control_c_function(void)
{
	ft_putchar_fd('\n', STDOUT);
	ft_display_prompt(PROMPT_COLOR, PROMPT_NAME);
	//printf(BOLDRED);
	//printf("\n\nCiao! 👋\n");
	//printf(COLOR_RESET);
	//exit(EXIT_SUCCESS);
}

static void	ft_control_backslash_function(void)
{
	exit(EXIT_SUCCESS);
}

/*
** FT_SIGNAL_HANDLER
** This function will be called in our "signal()" function to intercept the
** CTRL+C signal and instead of quitting our minishell we will just execute
** this function
** As per "signal()" function this function needs to be of a prototype
** "void ft(int n)", but in this case we don't need the int parameter
**
** Ctrl+C - SIGINT
** Ctrl+\ - SIGQUIT
*/

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
		ft_control_c_function();
	else if (sig == SIGQUIT)
		ft_control_backslash_function();
}
