/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:32:44 by ablondel          #+#    #+#             */
/*   Updated: 2021/07/21 18:21:16 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_count_env(char *s)
{
	int	n;

	n = 1;
	while (*s)
	{
		if (*s == ':')
			n++;
		s++;
	}
	return (n);
}

int		ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i] && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_dup_path(char *path)
{
	char *dst;
	int i;
	int len;

	dst = NULL;
	i = -1;
	len = 0;
	while (path[len])
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (path[++i])
		dst[i] = path[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_get_paths(char **env)
{
	unsigned int i;
	char	*dst;

	i = 0;
	dst = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 4) == 0)
		{
			dst = ft_dup_path(env[i] + 5);
			if (!dst)
				return (NULL);
		}
		i++;
	}
	return (dst);
}

char	**ft_split_env(t_msh *add, char *paths_var, char **paths)
{
	add->i = -1;
	add->j = 0;
	add->k = 0;
	paths = NULL;
	paths = (char **)malloc(sizeof(char *) * (ft_count_env(paths_var) + 1));
	if (!paths)
		return (NULL);
	while (++add->i < ft_count_env(paths_var))
	{
		paths[add->i] = (char *)malloc(sizeof(char) * (ft_strlen(paths_var) + 1));
		if (!paths[add->i])
			return (0);
		while (paths_var[add->j] && paths_var[add->j] == ':')
			add->j++;
		while (paths_var[add->j] && paths_var[add->j] != ':')
			paths[add->i][add->k++] = paths_var[add->j++];
		paths[add->i][add->k] = '\0';
		add->k = 0;
	}
	paths[add->i] = NULL;
	return (paths);
}

int	main(int ac, char **av, char **env)
{
	t_msh add;
	char	*all_paths;
	char	**paths;
	int i = 0;

	all_paths = NULL;
	paths = NULL;
	all_paths = ft_get_paths(env);
	printf("{%s}\n", all_paths);
	paths = ft_split_env(&add, all_paths, paths);
	while (paths[i])
	{
		printf("[%s]\n", paths[i]);
		i++;
	}
	return (0);
}
