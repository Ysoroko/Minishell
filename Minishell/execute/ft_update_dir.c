/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 11:15:43 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/15 11:18:53 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_pwd(void)
{
	char	buf[1024];
	char	*tmp;

	tmp = g_glob.env[ft_env_index("PWD")];
	getcwd(buf, 1024);
	g_glob.env[ft_env_index("PWD")] = ft_strjoin("PWD=", buf);
	free(tmp);
}

void	ft_update_oldpwd(void)
{
	char	buf[1024];
	char	*tmp;

	tmp = g_glob.env[ft_env_index("OLDPWD")];
	getcwd(buf, 1024);
	g_glob.env[ft_env_index("OLDPWD")] = ft_strjoin("OLDPWD=", buf);
	free(tmp);
}
