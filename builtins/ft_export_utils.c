/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:29:00 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/27 13:57:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_until(char *src, char c)
{
	int		i;
	int		len;
	char	*dst;

	i = -1;
	len = 0;
	dst = NULL;
	while (src[len] && src[len] != c)
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (src[++i] && src[i] != c)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
