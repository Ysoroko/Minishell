/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 14:13:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/26 14:18:12 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/// Calls malloc but if the call fails, calls exit(EXIT_FAILURE)
void	*ft_malloc_exit(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
		exit(EXIT_FAILURE);
	return (ret);
}
