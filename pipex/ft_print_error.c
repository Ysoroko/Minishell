/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:52:23 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 15:53:04 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(char *error, t_pipex *add)
{
	write(2, "pipex: ", 7);
	write(2, error, ft_len(error));
	write(2, ": ", 2);
	write(2, add->infile, ft_len(add->infile));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}
