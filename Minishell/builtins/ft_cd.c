/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:07:16 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/06 14:29:11 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(char *dst)
{
	if (!dst)
		if (chdir(ft_getenv("HOME")) == -1)
			printf("Minishell: %s: %s\n", dst, strerror(errno));
	chdir(dst);
	return ;
}
