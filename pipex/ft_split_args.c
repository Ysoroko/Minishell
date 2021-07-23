/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:55:39 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 16:12:32 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_split_arg(char *s, t_pipex *add)
{
	char	**strs;

	strs = NULL;
	add->i = -1;
	add->j = 0;
	add->k = 0;
	strs = (char **)malloc(sizeof(char *) * (ft_nb_options(s) + 2));
	if (!strs)
		return (NULL);
	while (++add->i < ft_nb_options(s))
	{
		strs[add->i] = (char *)malloc(sizeof(char) * (ft_len(s) + 1));
		if (!strs[add->i])
			return (ft_free_tab(strs));
		while (s[add->k] && s[add->k] != ' ')
			strs[add->i][add->j++] = s[add->k++];
		strs[add->i][add->j] = '\0';
		add->j = 0;
		add->k++;
	}
	strs[add->i] = 0;
	return (strs);
}
