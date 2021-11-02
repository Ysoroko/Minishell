/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:36:31 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/02 14:58:05 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_display_signal_message(int status_code)
{
	if (status_code == 131)
		ft_putendl_fd("Quit: 3", STDOUT);
	else if (status_code == 130)
		ft_putchar_fd('\n', STDOUT);
}

/*
** void	ft_control_c_function(void)
** This function is reposnsible for reaction to "CTRL + C" input from the user
** CTRL + C sends an "interrupt" signal, which discards previous input and
** displays a new prompt on a newline
*/

static void	ft_control_c_function(void)
{
	if (!g_glob.fork_ret)
	{
		ft_modify_exit_status(1);
		ft_putchar_fd('\n', STDOUT);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
** void	ft_control_backslash_function(void)
** This function is reposnsible for reaction to "CTRL + \" input from the user
** CTRL + \ sends a "quit" signal, which exits the child process and dumps core
** Does nothing in the main process.
*/

static void	ft_control_backslash_function(void)
{
	if (!g_glob.fork_ret)
	{
		rl_on_new_line();
		rl_redisplay();
	}
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
** Ctrl+D (without user input) = same as Ctrl+\, SIGQUIT but without core dump
** Ctrl+D (with input) = does nothing
*/

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
		ft_control_c_function();
	else if (sig == SIGQUIT)
		ft_control_backslash_function();
}

/*
** FT_SETUP_SIGNALS
** This function modifies the behaviour when specific actions are done
** SIGINT = CTRL + C is pressed
** SIGQUIT = CTRL + \ is pressed
** SIGUSR1 = CTRL + D is pressed (not a signal, I'm using SIGUSR1 for ease)
*/

void	ft_setup_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
}
