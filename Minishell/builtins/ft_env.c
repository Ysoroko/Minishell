/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:16:10 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/24 15:54:28 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_equal_sign(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	while (env[i])
	{
		if (ft_check_equal_sign(env[i]))
			write(1, &env[i], ft_strlen(env[i]));
		i++;
	}
	return (0);
}
