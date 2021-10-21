/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:57:11 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/21 12:17:12 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit(int n)
{
	char	*temp;
	char	*n_str;

	n_str = ft_itoa_exit(n);
	temp = ft_strjoin_exit("EXIT_STATUS=", n_str);
	g_glob.exit_status = n;
	g_glob.env = ft_export(temp);
	free(n_str);
	free(temp);
	exit(n);
}
