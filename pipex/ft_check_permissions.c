/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_permissions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:53:57 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 16:07:18 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_permissions(t_pipex *add, char **av)
{
	extern int	errno;

	add->infile = ft_strdup(av[1]);
	if (!add->infile)
		ft_print_error(strerror(errno), add);
	if ((access(add->infile, F_OK) == -1) || (access(add->infile, R_OK) == -1))
		ft_print_error(strerror(errno), add);
}
