/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:44:54 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/20 09:14:30 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_up_shlvl(void)
{
	char	buf[1024];
	char	*tmp;
	char	*next;
	int		n;

	tmp = ft_strdup(g_glob.env[ft_env_index("SHLVL")]);
	n = ft_atoi(tmp + 6) + 1;
	free(tmp);
	tmp = g_glob.env[ft_env_index("SHLVL")];
	g_glob.env[ft_env_index("SHLVL")] = ft_strjoin("SHLVL=", ft_itoa(n));
	if (g_glob.env[ft_env_index("SHLVL")] == NULL)
		ft_minishell_error(strerror(errno));
	else
		free(tmp);
}

void	ft_down_shlvl(void)
{
	char	buf[1024];
	char	*tmp;
	int		n;

	tmp = ft_strdup(g_glob.env[ft_env_index("SHLVL")]);
	n = ft_atoi(tmp + 6) - 1;
	free(tmp);
	tmp = g_glob.env[ft_env_index("SHLVL")];
	g_glob.env[ft_env_index("SHLVL")] = ft_strjoin("SHLVL=", ft_itoa(n));
	if (g_glob.env[ft_env_index("SHLVL")] == NULL)
		ft_minishell_error(strerror(errno));
	else
		free(tmp);
}
