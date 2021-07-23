/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 07:06:08 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 17:14:11 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split(t_pipex *add)
{
	add->strs = NULL;
	add->i = -1;
	add->j = 0;
	add->k = 0;
	add->strs = (char **)malloc(sizeof(char *) * (ft_nb_paths(add->s) + 1));
	if (!add->strs)
		return (NULL);
	while (++add->i < ft_nb_paths(add->s))
	{
		add->strs[add->i] = (char *)malloc(sizeof(char) * (ft_len(add->s) + 2));
		if (!add->strs[add->i])
			return (ft_free_tab(add->strs));
		while (add->s[add->k] && add->s[add->k] != ':')
			add->strs[add->i][add->j++] = add->s[add->k++];
		add->strs[add->i][add->j] = '/';
		add->strs[add->i][add->j + 1] = '\0';
		add->j = 0;
		add->k++;
	}
	add->strs[add->i] = 0;
	return (add->strs);
}
