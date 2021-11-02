/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:22:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/27 16:43:18 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_err(char *cmd, char *wrong_arg, char *error_message, int err)
{
	ft_putstr_fd(PROMPT_ERROR, STDERR);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (wrong_arg)
	{
		ft_putstr_fd(wrong_arg, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putendl_fd(error_message, STDERR);
	if (err)
		ft_modify_exit_status(err);
}
