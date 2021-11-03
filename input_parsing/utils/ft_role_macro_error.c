/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_role_macro_error.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:36:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/03 11:43:20 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_role_macro_error(char *current_element)
{
	if ((ft_n_chars_in_str(current_element, '>') > 2
			|| ft_n_chars_in_str(current_element, '<') > 2)
		&& ft_str_only_has_chars_from_charset(current_element,
			SPACES_AND_REDIRECTIONS))
		return (1);
	if (ft_str_only_has_chars_from_charset(current_element,
			SPACES_REDIRS_PIPES) && ft_strchr(current_element, '|')
		&& (ft_strchr(current_element, '>')
			|| ft_strchr(current_element, '<')))
		return (1);
	return (0);
}

int	ft_error_macro_present(int *macros, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if (macros[i] == ERROR)
			return (1);
	}
	return (0);
}
