/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:44:54 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/26 16:24:01 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_up_shlvl(void)
{
	char	buf[1024];
	char	*tmp;
	char	*next;
	int		n;
	char	*itoad;

	tmp = ft_strdup(g_glob.env[ft_env_index("SHLVL")]);
	n = ft_atoi(tmp + 6) + 1;
	free(tmp);
	tmp = g_glob.env[ft_env_index("SHLVL")];
	itoad = ft_itoa_exit(n);
	g_glob.env[ft_env_index("SHLVL")] = ft_strjoin("SHLVL=", itoad);
	free(tmp);
	free(itoad);
	if (g_glob.env[ft_env_index("SHLVL")] == NULL)
		ft_minishell_error(strerror(errno));
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
	g_glob.env[ft_env_index("SHLVL")] = ft_strjoin("SHLVL=", ft_itoa_exit(n));
	free(tmp);
	if (g_glob.env[ft_env_index("SHLVL")] == NULL)
		ft_minishell_error(strerror(errno));
}
