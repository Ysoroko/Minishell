/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_pref_exit.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 12:35:05 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/14 13:12:15 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** FT_STRJOIN_FREE_PREF_EXIT
** Same as ft_strjoin, but the previous value of *pref is freed so we can
** realloc it while joining the two strings
*/

char	*ft_strjoin_free_pref_exit(char **pref, char *suff)
{
	char	*ret;

	if (!pref)
		return (0);
	if (!*pref)
		return (ft_strdup_exit(suff));
	if (!suff)
		return (*pref);
	ret = ft_strjoin_exit(*pref, suff);
	ft_free_str(pref);
	return (ret);
}
