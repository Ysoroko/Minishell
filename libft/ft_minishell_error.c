/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:30:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/27 16:42:52 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/// Prints "minishell in cyan followed by its argument"
/// Example: ft_minishell_error("syntax error near unexpected token \')\'"");
/// Results in:
/// "minishell: syntax error near unexpected token ')'"
void	ft_minishell_error(char *error_message)
{
	ft_putstr_fd(PROMPT_ERROR, STDERR);
	ft_putendl_fd(error_message, STDERR);
}
