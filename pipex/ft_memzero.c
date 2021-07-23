/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 07:03:48 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 16:58:31 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_memzero(unsigned int len)
{
	char	*dst;

	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (len)
		dst[--len] = '\0';
	return (dst);
}
