/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:44:54 by ablondel          #+#    #+#             */
/*   Updated: 2021/11/02 14:57:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_up_shlvl(void)
{
	char	*tmp;
	int		n;
	char	*itoad;

	tmp = ft_strdup_exit(g_glob.env[ft_env_index("SHLVL")]);
	n = ft_atoi(tmp + 6) + 1;
	free(tmp);
	tmp = g_glob.env[ft_env_index("SHLVL")];
	itoad = ft_itoa_exit(n);
	g_glob.env[ft_env_index("SHLVL")] = ft_strjoin_exit("SHLVL=", itoad);
	free(tmp);
	free(itoad);
	if (g_glob.env[ft_env_index("SHLVL")] == NULL)
		ft_minishell_error(strerror(errno));
}

void	ft_down_shlvl(void)
{
	char	*tmp;
	int		n;
	char	*itoad;

	tmp = ft_strdup_exit(g_glob.env[ft_env_index("SHLVL")]);
	n = ft_atoi(tmp + 6) - 1;
	free(tmp);
	tmp = g_glob.env[ft_env_index("SHLVL")];
	itoad = ft_itoa_exit(n);
	g_glob.env[ft_env_index("SHLVL")] = ft_strjoin_exit("SHLVL=", itoad);
	free(tmp);
	free(itoad);
	if (g_glob.env[ft_env_index("SHLVL")] == NULL)
		ft_minishell_error(strerror(errno));
}
