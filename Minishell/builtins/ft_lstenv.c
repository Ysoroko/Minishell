/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:34:24 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/23 16:25:56 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_list	*ft_tab_to_list(void)
{
	t_list	*lst;
	t_list	*new;
	int		i;

	i = 0;
	lst = NULL;
	while (g_glob.env[i])
	{
		new = ft_lstnew(ft_strdup((char *)g_glob.env[i]));
		if (!new)
			return (NULL);
		ft_lstadd_back(&lst, new);
		i++;
	}
	return (lst);
}

void	ft_clear_node(void *content)
{
	if (!content)
		return ;
	free(content);
}

char	**ft_list_to_tab(t_list *lst)
{
	int		i;
	char	**next_env;

	i = 0;
	next_env = NULL;
	next_env = (char **)malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	if (!next_env)
		return (NULL);
	while (lst)
	{
		next_env[i] = ft_strdup(lst->content);
		if (!next_env[i])
			return (NULL);
		lst = lst->next;
		i++;
	}
	next_env[i] = NULL;
	return (next_env);
}

void	ft_delete(t_list **lst, char *var)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *lst;
	prev = NULL;
	if (ft_cmp_env(tmp->content, var) == 0)
	{
		*lst = tmp->next;
		free(tmp->content);
		free(tmp);
		return ;
	}
	else
	{
		while (ft_cmp_env(tmp->content, var) != 0)
		{
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == NULL)
			return ;
		prev->next = tmp->next;
		free(tmp->content);
		free(tmp);
	}
}
