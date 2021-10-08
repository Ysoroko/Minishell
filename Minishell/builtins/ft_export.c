/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:48:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/08 07:46:32 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_export(char *new_var)
{
	int		i;
	char	**next_env;

	i = 0;
	next_env = NULL;
	next_env = (char **)malloc(sizeof(char *) * (ft_nb_env(g_glob.env) + 2));
	if (!next_env)
		return (NULL);
	next_env[i] = ft_strdup_exit(g_glob.env[i]);
	while (i < ft_nb_env(g_glob.env))
	{
		next_env[i] = ft_strdup_exit(g_glob.env[i]);
		if (!next_env[i])
			return (NULL);
		i++;
	}
	next_env[i] = ft_strdup_exit(new_var);
	next_env[i + 1] = NULL;
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
			if (s[i + 1] == '\0')
			{
				write(1, "\"\n", 2);
				return ;
			}
		}
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\"\n", 2);
}

void	ft_print(void)
{
	int	i;

	i = 0;
	while (g_glob.env[i])
	{
		write(1, "declare -x ", 11);
		ft_format(g_glob.env[i]);
		i++;
	}
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
