/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:30:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/08 12:34:42 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/// Prints "minishell in cyan followed by its argument"
/// Example: ft_minishell_error("syntax error near unexpected token \')\'"");
/// Results in:
/// "minishell: syntax error near unexpected token ')'"
void	ft_minishell_error(char *error_message)
{
	ft_putstr_fd("\033[1m\033[36mminishell: \x1b[0m ", STDERR);
	ft_putstr_fd(error_message, STDERR);
}
