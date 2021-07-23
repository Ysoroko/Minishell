/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 07:02:24 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 17:06:22 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dst;

	i = -1;
	if (!src)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_len(src) + 1));
	if (!dst)
		return (NULL);
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
