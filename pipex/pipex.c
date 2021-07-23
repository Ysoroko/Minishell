/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 07:21:06 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 17:19:38 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_check_cmd(t_pipex *add, char *cmd)
{
	add->i = 0;
	while (add->paths[add->i])
	{
		add->tmp = ft_strjoin(add->paths[add->i], cmd);
		if (access(add->tmp, X_OK) == 0)
			return (0);
		add->i++;
	}
	write(2, "pipex: ", 7);
	write(2, "command not found", 17);
	write(2, ": ", 2);
	write(2, cmd, ft_len(cmd));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
	return (-1);
}

int	main(int ac, char **av, char **env)
{
	t_pipex	add;

	if (ac == 5)
	{
		ft_check_permissions(&add, av);
		if (ft_setup_args(&add, av, env) == NULL)
			exit(EXIT_FAILURE);
		if (pipe(add.pfd) == -1)
			exit(EXIT_FAILURE);
		ft_check_cmd(&add, add.args1[0]);
		ft_check_cmd(&add, add.args2[0]);
		add.p1 = fork();
		if (add.p1 < 0)
			exit(EXIT_FAILURE);
		if (add.p1 == 0)
			ft_child_one(&add);
		add.p2 = fork();
		if (add.p2 < 0)
			exit(EXIT_FAILURE);
		if (add.p2 == 0)
			ft_child_two(&add);
		ft_parent(&add);
	}
	exit(EXIT_SUCCESS);
}
