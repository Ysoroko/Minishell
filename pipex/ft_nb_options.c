/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:54:35 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 16:10:35 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_wsp(char c)
{
	if (c == '\v' || c == '\r' || c == '\t' || c == '\f' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

int	ft_nb_options(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (!s)
		return (1);
	while (s[i])
	{
		if (ft_wsp(s[i - 1]) && !ft_wsp(s[i]))
			n++;
		i++;
	}
	return (n);
}
