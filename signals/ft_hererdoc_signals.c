/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hererdoc_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:28:00 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/02 18:44:45 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_wait_and_update_exit_status_hdoc(void)
{
	int	status;
	int	status_code;

	waitpid(0, &status, 0);
	if (g_glob.fork_ret > 0)
	{
		if (WIFEXITED(status))
		{
			status_code = WEXITSTATUS(status);
			ft_modify_exit_status(status_code);
		}
		else if (WIFSIGNALED(status))
		{
			status_code = 128 + WTERMSIG(status);
			ft_modify_exit_status(status_code);
		}
	}
	g_glob.fork_ret = 0;
}

static void	ft_heredoc_signal_handler(int sig)
{
	if (!g_glob.fork_ret)
	{
		if (sig == SIGINT)
			exit(EXIT_FAILURE);
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
	else
	{
		if (sig == SIGINT)
			ft_putchar_fd('\n', STDOUT);
	}
}

void	ft_heredoc_signals_setup(void)
{
	signal(SIGINT, ft_heredoc_signal_handler);
	signal(SIGQUIT, ft_heredoc_signal_handler);
}
