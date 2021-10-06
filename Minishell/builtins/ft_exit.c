/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:57:11 by ablondel          #+#    #+#             */
/*   Updated: 2021/10/01 19:59:30 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exit()
{
	kill(g_glob.main_pid, SIGUSR1);
	kill(0, SIGUSR1);
	exit(EXIT_SUCCESS);
}
