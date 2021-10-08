/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 07:02:26 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 07:13:05 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_nb_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	ft_cmp_env(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*(s1 + 1) && *(s1 + 1) == '=')
			return (0);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_env_index(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = ft_nb_env(g_glob.env);
	while (g_glob.env[i] && i < j)
	{
		if (ft_cmp_env(g_glob.env[i], s) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_duplicate_env(char **env)
{
	int	i;

	i = 0;
	g_glob.env = (char **)malloc(sizeof(char *) * (ft_nb_env(env) + 1));
	if (!g_glob.env)
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
	while (i < ft_nb_env(env))
	{
		g_glob.env[i] = ft_strdup_exit(env[i]);
		i++;
	}
	g_glob.env[i] = NULL;
}

char	*ft_getenv(char *s)
{
	if (ft_env_index >= 0)
		return (g_glob.env[ft_env_index(s)] + (ft_strlen(s) + 1));
	return (NULL);
}
