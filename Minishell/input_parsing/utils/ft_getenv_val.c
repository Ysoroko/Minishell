/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:08:53 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/25 16:27:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// returns a malloc'd copy of value of the env variable
char	*ft_getenv_val(char *str)
{
	char	*temp;
	char	*ret;
	int		i;
	int		index;

	index = ft_env_index(str);
	if (index == -1)
		return (ft_strdup_exit(""));
	temp = g_glob.env[i];
	i = 0;
	while (temp[i] && temp[i] != '=')
		i++;
	if (temp[i])
		i++;
	return (ft_strdup_exit(&(temp[i])));
}
