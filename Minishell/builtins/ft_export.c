/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:48:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/04 13:13:27 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **ft_export(char *new_var)
{
	int		i = 0;
	char	**next_env = NULL;

	next_env = (char**)malloc(sizeof(char*) * (ft_nb_env(g_glob.env) + 1));
	if (!next_env)
		return (NULL);
	next_env[i] = ft_strdup_exit(g_glob.env[i]);
	while (i < ft_nb_env(g_glob.env))
	{
		if (!(next_env[i] = ft_strdup_exit(g_glob.env[i])))
			return (NULL);
		i++;
	}
	next_env[i] = ft_strdup_exit(new_var);
	next_env[i + 1] = NULL;
	return (next_env);
}
