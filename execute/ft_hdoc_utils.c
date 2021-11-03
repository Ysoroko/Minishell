/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hdoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:48:02 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/03 11:01:52 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_open_hdoc_file(t_command *cmd, int *fd)
{
	char	*path_to_file;
	char	*path;

	path = cmd->path;
	path_to_file = ft_strjoin_exit(path, "tmp");
	if (ft_check_file_permissions(path_to_file) >= 1)
		*fd = open(path_to_file, O_RDWR | O_CREAT | O_TRUNC, 0664);
	else
		*fd = open(path_to_file, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (*fd == -1)
	{
		ft_minishell_error(strerror(errno));
		cmd->error = 1;
		free(path_to_file);
		ft_exit(errno);
	}
	free(path_to_file);
}
