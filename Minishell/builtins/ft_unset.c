/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:27:27 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 00:56:23 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **ft_unset(char *var)
{
	int i;
	int j;
	int skip;
	char **next_env;

	i = 0;
	j = 0;
	skip = ft_env_index(var);
	next_env = NULL;
	next_env = (char**)malloc(sizeof(char*) * (ft_nb_env(g_glob.env) + 1));
	if (!next_env)
		return (NULL);
	next_env[j] = ft_strdup_exit(g_glob.env[i]);
	i++;
	j++;
	while (g_glob.env[i])
	{
		if (i == skip)
			i++;
		if (g_glob.env[i] != NULL)
			next_env[j] = ft_strdup_exit(g_glob.env[i]);
		else
			break ;
		i++;
		j++;
	}
	next_env[j] = NULL;
	return (next_env);
}
