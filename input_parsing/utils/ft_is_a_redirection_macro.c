/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_a_redirection_macro.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:41:52 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/03 10:42:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_is_a_redirection_macro(int m)
{
	if (m == REDIR_L || m == REDIR_LL || m == REDIR_R || m == REDIR_RR)
		return (1);
	return (0);
}
