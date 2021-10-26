/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:15:43 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/26 13:17:00 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_pwd(void)
{
	char	buf[1024];
	char	*tmp;

	tmp = g_glob.env[ft_env_index("PWD")];
	getcwd(buf, 1024);
	g_glob.env[ft_env_index("PWD")] = ft_strjoin_exit("PWD=", buf);
	free(tmp);
}

void	ft_update_oldpwd(void)
{
	char	buf[1024];
	int		index;
	char	*tmp;

	index = ft_env_index("OLDPWD");
	if (index == -1)
		return ;
	tmp = g_glob.env[index];
	getcwd(buf, 1024);
	g_glob.env[ft_env_index("OLDPWD")] = ft_strjoin_exit("OLDPWD=", buf);
	free(tmp);
}
