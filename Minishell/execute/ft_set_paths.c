/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:27:28 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 06:28:01 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split_paths(int *i)
{
	char	*tmp;
	char	**paths;

	*i = -1;
	paths = NULL;
	tmp = getenv("PATH");
	if (!tmp)
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
	paths = ft_split(tmp, ':');
	if (!paths)
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
	return (paths);
}

void	ft_join_paths(char **paths, char *tmp, int i)
{
	tmp = paths[i];
	paths[i] = ft_strjoin_exit(paths[i], "/");
	if (tmp[0])
		free(tmp);
	if (paths[i] == NULL)
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
}

int	ft_set_paths(char **exec_name)
{
	int		i;
	char	*tmp;
	char	**paths;

	paths = ft_split_paths(&i);
	while (paths[++i])
	{
		ft_join_paths(paths, tmp, i);
		if (ft_exec_check(paths[i], *exec_name) == 1)
		{
			tmp = *exec_name;
			*exec_name = ft_strjoin_exit(paths[i], *exec_name);
			if (tmp[0])
				free(tmp);
			if (*exec_name == NULL)
			{
				printf("%s\n", strerror(ENOMEM));
				return (-1);
			}
			return (1);
		}
	}
	return (0);
}
