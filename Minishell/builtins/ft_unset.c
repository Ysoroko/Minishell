/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:27:27 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 07:17:34 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init(int *i, int *j, char **next_env)
{
	*i = 0;
	*j = 0;
	next_env = (char **)malloc(sizeof(char *) * (ft_nb_env(g_glob.env) + 1));
	if (!next_env)
	{
		printf("minishell: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

char	**ft_unset(char *var)
{
	int		i;
	int		j;
	int		skip;
	char	**next_env;

	skip = ft_env_index(var);
	ft_init(&i, &j, next_env);
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

void	ft_unset_handler(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->str_tab_for_execve[i])
	{
		if (ft_env_index(cmd->str_tab_for_execve[i]) >= 0)
			g_glob.env = ft_unset(cmd->str_tab_for_execve[i]);
		i++;
	}
}
