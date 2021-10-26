/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:27:27 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/26 17:31:33 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_unset(char *var)
{
	t_list	*lst;

	lst = ft_tab_to_list();
	if (!lst)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	ft_free_str_tab(&g_glob.env, NULL);
	ft_delete(&lst, var);
	g_glob.env = ft_list_to_tab(lst);
	if (!g_glob.env)
	{
		ft_minishell_error(strerror(errno));
		ft_exit(errno);
	}
	ft_lstclear(&lst, &ft_clear_node);
}

void	ft_unset_handler(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->str_tab_for_execve[i])
	{
		if (ft_env_index(cmd->str_tab_for_execve[i]) >= 0)
			ft_unset(cmd->str_tab_for_execve[i]);
		i++;
	}
	ft_modify_exit_status(0);
}
