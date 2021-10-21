/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:48:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/21 15:12:01 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_export(char *new_var)
{
	int		i;
	char	**next_env;

	i = 1;
	next_env = NULL;
	next_env = (char **)malloc(sizeof(char *) * (ft_nb_env(g_glob.env) + 1));
	if (!next_env)
		return (NULL);
	next_env[0] = ft_strdup_exit(g_glob.env[0]);
	while (i < ft_nb_env(g_glob.env))
	{
		next_env[i] = ft_strdup_exit(g_glob.env[i]);
		free(g_glob.env[i]);
		if (!next_env[i])
			return (NULL);
		i++;
	}
	next_env[i] = ft_strdup_exit(new_var);
	next_env[i + 1] = NULL;
	free(g_glob.env);
	return (next_env);
}

void	ft_format(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i - 1] == '=')
		{
			write(1, "\"", 1);
		}
		write(1, &s[i], 1);
		if (s[i + 1] == '\0')
		{
			write(1, "\"\n", 2);
			return ;
		}
		i++;
	}
	write(1, "\"\n", 2);
}

char	**ft_copy_for_print(char **sorted)
{
	int		i;
	char	*tmp;

	i = 0;
	sorted = NULL;
	sorted = (char **)malloc(sizeof(char *) * (ft_nb_env(g_glob.env) + 1));
	if (!sorted)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	while (g_glob.env[i])
	{
		sorted[i] = ft_strdup(g_glob.env[i]);
		if (!sorted[i])
		{
			ft_minishell_error(strerror(errno));
			ft_exit(errno);
		}
		i++;
	}
	sorted[i] = NULL;
	return (sorted);
}

void	ft_print(void)
{
	int		i;
	char	*tmp;
	char	**sorted;

	i = 0;
	sorted = ft_copy_for_print(sorted);
	while (i + 1 < ft_nb_env(sorted))
	{
		if (ft_strcmp(sorted[i], sorted[i + 1]) > 0)
		{
			tmp = sorted[i];
			sorted[i] = sorted[i + 1];
			sorted[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	i = -1;
	while (sorted[++i])
	{
		write(1, "declare -x ", 11);
		ft_format(sorted[i]);
	}
	ft_free_str_tab(&sorted, NULL);
}

void	ft_export_handler(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 1;
	if (cmd->str_tab_for_execve[i] == NULL)
		ft_print();
	while (cmd->str_tab_for_execve[i])
	{
		if (ft_env_index(cmd->str_tab_for_execve[i]) >= 0)
		{
			g_glob.env = ft_unset(cmd->str_tab_for_execve[i]);
			g_glob.env = ft_export(cmd->str_tab_for_execve[i]);
		}
		else
			g_glob.env = ft_export(cmd->str_tab_for_execve[i]);
		i++;
	}
}
