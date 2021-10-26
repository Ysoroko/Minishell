/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:22:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/26 13:32:25 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_err_gen(char *cmd, char *wrong_arg, char *error_message)
{
	ft_putstr_fd("\033[1m\033[36mminishell: \x1b[0m", STDERR);
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
}
