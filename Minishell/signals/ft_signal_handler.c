/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:36:31 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/24 16:02:20 by ysoroko          ###   ########.fr       */
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
	//char *dup = ft_strdup_exit(g_glob.buffer);
	ft_putchar_fd('\n', STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//ft_prompt();
}

/*
** void	ft_control_backslash_function(void)
** This function is reposnsible for reaction to "CTRL + D" input from the user
** CTRL + D sends a "quit" signal, which exits current process and dumps core
** This is achieved by sending a "SIGABRT" signal to our own process.
*/

static void	ft_control_backslash_function(void)
{
	// for some reason now it "blocks" the previously entered string
	//printf("CTRL + \\ have been pressed");
	kill(getpid(), SIGCONT);
	exit(EXIT_SUCCESS);
}

/*
** ft_control_d_empty_input_function(void)
** This signal is caught when CTRL+D is pressed and the input is empty
** It exits the process and displays "exit" in terminal.
** Does not dump core ("unlike CTRL + \").
*/

static void	ft_control_d_empty_input_function(void)
{
	close(STDIN);
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
