/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:27:27 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/15 06:55:51 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset_init(int *i, int *j, int *skip, char *var)
{
	*i = 1;
	*j = 1;
	*skip = ft_env_index(var);
}

char	**ft_unset(char *var)
{
	int		i;
	int		j;
	int		skip;
	char	**next_env;

	ft_unset_init(&i, &j, &skip, var);
	next_env = (char **)malloc(sizeof(char *) * (ft_nb_env(g_glob.env) + 1));
	if (!next_env)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	next_env[0] = ft_strdup_exit(g_glob.env[0]);
	while (g_glob.env[i])
	{
		if (g_glob.env[i] != NULL && i != skip)
			next_env[j++] = ft_strdup_exit(g_glob.env[i++]);
		else
			break ;
	}
	ft_free_str_tab(&g_glob.env, NULL);
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
