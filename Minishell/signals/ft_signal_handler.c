/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:36:31 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/01 15:52:10 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** void	ft_control_c_function(void)
** This function is reposnsible for reaction to "CTRL + C" input from the user
** CTRL + C sends an "interrupt" signal, which discards previous input and
** displays a new prompt on a newline
*/

static void	ft_control_c_function(void)
{
	if (g_glob.fork_ret == g_glob.main_pid)
	{
		ft_putchar_fd('\n', STDOUT);
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
	}
	else
	{
		ft_putchar_fd('\n', STDOUT);
	}
}

/*
** void	ft_control_backslash_function(void)
** This function is reposnsible for reaction to "CTRL + D" input from the user
** CTRL + D sends a "quit" signal, which exits current process and dumps core
*/

static void	ft_control_backslash_function(void)
{
	if (g_glob.fork_ret == g_glob.main_pid)
	{
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		ft_putendl_fd("Quit: 3", STDOUT);
	}
}

/*
** ft_control_d_empty_input_function(void)
** Not an actual signal.
** This signal is caught when CTRL+D is pressed and the input is empty
** It exits the process and displays "exit" in terminal.
** Does not dump core ("unlike CTRL + \").
*/

static void	ft_control_d_empty_input_function(void)
{
	ft_putendl_fd("exit", STDOUT);
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
** Ctrl+D (without user input) = same as Ctrl+\, SIGQUIT but without core dump
** Ctrl+D (with input) = does nothing
*/

void	ft_signal_handler(int sig)
{
	if (sig == SIGINT)
		ft_control_c_function();
	else if (sig == SIGQUIT)
		ft_control_backslash_function();
	else if (sig == SIGUSR1)
		ft_control_d_empty_input_function();
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
	signal(SIGUSR1, ft_signal_handler);
}
