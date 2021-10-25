/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:40:43 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/25 16:58:56 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	main(int ac, char **av, char **env)
{
	char	buf[1024];

	(void)ac;
	(void)av;
	(void)env;
	getcwd(buf, 1024);
	printf("%s\n", buf);
	ft_modify_exit_status(0);
	return (0);
}
