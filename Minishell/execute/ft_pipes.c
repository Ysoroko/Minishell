/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:19:33 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 07:19:56 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close_pipes(int npipes, int *pfd)
{
	int	i;

	i = 0;
	while (i < (npipes * 2))
	{
		if (close(pfd[i]) == -1)
		{
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	ft_open_pipes(int npipes, int *pfd)
{
	int	i;

	i = 0;
	while (i < npipes)
	{
		if (pipe(pfd + i * 2) == -1)
		{
			printf("%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
