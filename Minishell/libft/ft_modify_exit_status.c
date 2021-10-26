/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify_exit_status.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:27:34 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/26 11:04:51 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include "../include/minishell.h"

void	ft_modify_exit_status(int new_value)
{
	char	*str;
	char	*new_value_as_str;

	new_value_as_str = ft_itoa_exit(new_value);
	str = ft_strjoin_exit("EXIT_STATUS=", new_value_as_str);
	ft_unset("EXIT_STATUS");
	ft_export(str);
	free(new_value_as_str);
	free(str);
}
