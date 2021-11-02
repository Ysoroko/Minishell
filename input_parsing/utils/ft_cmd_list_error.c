/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_list_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:04:09 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/02 17:18:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_setup_variables(t_command **tmp, t_dl_lst *l, int **t, int *len)
{
	*tmp = (t_command *)(l->content);
	*t = (*tmp)->role_macros;
	*len = ft_str_tab_len((*tmp)->str_tab_all);
	return (0);
}

static int	ft_error_found(void)
{
	ft_minishell_error("syntax error");
	ft_modify_exit_status(258);
	return (1);
}

static int	ft_pipe_error(t_dl_lst *next)
{
	t_command	*next_command;

	if (!next)
		return (1);
	next_command = (t_command *)(next->content);
	if (next_command->role_macros[0] != COMMAND
		&& !ft_is_a_redir_arg_macro((next_command->role_macros)[1]))
	{
		return (1);
	}
	return (0);
}

static int	ft_redir_error(int *macros, int len, char **str_tab_all)
{
	int		i;
	char	*str;

	i = -1;
	while (++i <= len)
	{
		str = str_tab_all[i];
		if (ft_str_is_a_redirection(str))
		{
			if (i + 1 > len || !ft_is_a_redir_arg_macro(macros[i + 1]))
				return (1);
		}
	}
	return (0);
}

int	ft_cmd_list_error(t_dl_lst *lst)
{
	t_dl_lst	*current;
	t_command	*temp;
	int			*tab;
	int			len;

	current = lst;
	while (current)
	{
		ft_setup_variables(&temp, current, &tab, &len);
		if (tab[len - 1] == PIPE && ft_pipe_error(current->next))
			return (ft_error_found());
		if (ft_redir_error(tab, len, temp->str_tab_all))
			return (ft_error_found());
		current = current->next;
	}
	return (0);
}
