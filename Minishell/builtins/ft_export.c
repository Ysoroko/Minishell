/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 12:48:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/23 16:27:59 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_format(char *s)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	while (s[i])
	{
		if (s[i] == '=')
			equal = 1;
		if (s[i - 1] == '=')
			write(1, "\"", 1);
		write(1, &s[i], 1);
		if (s[i + 1] == '\0' && equal == 1)
		{
			write(1, "\"\n", 2);
			return ;
		}
		i++;
	}
	if (equal == 1)
		write(1, "\"", 1);
	write(1, "\n", 1);
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

void	ft_export(char *new_var)
{
	t_list	*lst;
	t_list	*new;

	lst = ft_tab_to_list();
	if (!lst)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	ft_free_str_tab(&g_glob.env, NULL);
	new = ft_lstnew(ft_strdup(new_var));
	if (!new)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup(new_var)));
	g_glob.env = ft_list_to_tab(lst);
	if (!g_glob.env)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	ft_lstclear(&lst, &ft_clear_node);
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
			ft_unset(cmd->str_tab_for_execve[i]);
			ft_export(cmd->str_tab_for_execve[i]);
		}
		else
			ft_export(cmd->str_tab_for_execve[i]);
		i++;
	}
}
