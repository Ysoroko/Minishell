/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:49:00 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/15 10:33:56 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_update_pwd(void)
{
	char	buf[1024];
	char	*tmp;
	int		index;

	index = ft_env_index("PWD");
	if (index == -1)
		return ;
	tmp = g_glob.env[ft_env_index("PWD")];
	if (!getcwd(buf, 1024))
	{
		ft_err(NULL, NULL, strerror(errno), 1);
		return ;
	}
	g_glob.env[ft_env_index("PWD")] = ft_strjoin_exit("PWD=", buf);
	free(tmp);
}

static void	ft_update_oldpwd(char *str)
{
	int		index;
	char	*tmp;

	index = ft_env_index("OLDPWD");
	if (index == -1)
	{
		tmp = ft_strjoin_exit("OLDPWD=", str);
		ft_export(tmp);
		free(tmp);
		return ;
	}
	tmp = g_glob.env[index];
	g_glob.env[ft_env_index("OLDPWD")] = ft_strjoin_exit("OLDPWD=", str);
	free(tmp);
}

void	ft_cd(t_command *cmd)
{
	char	*arg;
	char	oldpwd[1024];

	arg = (cmd->str_tab_for_execve)[1];
	if (!arg)
		arg = ft_getenv("HOME");
	else if (ft_str_only_has_chars_from_charset(arg, SPACES))
		return ;
	else if (ft_strlen(arg) > 255)
	{
		ft_err("cd", arg, "File name too long", 1);
		return ;
	}
	if (!getcwd(oldpwd, 1024) || chdir(arg) == -1)
	{
		ft_err("cd", arg, strerror(errno), 1);
		return ;
	}
	ft_update_oldpwd(oldpwd);
	ft_update_pwd();
	ft_modify_exit_status(0);
}
