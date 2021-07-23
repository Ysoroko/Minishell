/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:21:13 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 16:24:49 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_setup_args(t_pipex *add, char **av, char **env)
{
	if (ft_set_all_paths(add, env) == NULL)
		return (NULL);
	add->args1 = ft_split_arg(av[2], add);
	add->args2 = ft_split_arg(av[3], add);
	add->infile = ft_strdup(av[1]);
	add->outfile = ft_strdup(av[4]);
	if (!add->args1 || !add->args2 || !add->infile || !add->outfile)
		return (NULL);
	return ("YEEEEEH!");
}
