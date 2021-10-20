/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 06:27:28 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/20 11:44:50 by ablondel         ###   ########.fr       */
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
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	paths = ft_split(tmp, ':');
	if (!paths)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	return (paths);
}

void	ft_join_paths(char **paths, char *tmp, int i)
{
	(void)tmp;
	char	*tmp1;

	tmp1 = paths[i];
	paths[i] = ft_strjoin(paths[i], "/");
	free(tmp1);
	if (paths[i] == NULL)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
}

int	ft_set_paths(char **exec_name)
{
	int		i;
	char	*tmp;
	char	**paths;

	paths = ft_split_paths(&i);
	if (!paths)
		return (-1);
	i = -1;
	while (paths[++i])
	{
		ft_join_paths(paths, tmp, i);
		if (ft_exec_check(paths[i], *exec_name) == 1)
		{
			tmp = *exec_name;
			*exec_name = ft_strjoin(paths[i], *exec_name);
			ft_free_str_tab(&paths, NULL);
			free(tmp);
			if (*exec_name == NULL)
			{
				ft_minishell_error(strerror(errno));
				return (-1);
			}
			return (1);
		}
	}
	ft_free_str_tab(&paths, NULL);
	return (0);
}
