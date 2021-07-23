/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_all_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:51:04 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 17:53:15 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_set_all_paths(t_pipex *add, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
		{
			add->s = ft_strdup(&env[i][5]);
			if (!add->s)
				return (NULL);
			add->paths = ft_split(add);
			if (!add->paths)
				return (*ft_free_tab(add->paths));
		}
	}
	return ("YEEEEEH!");
}
