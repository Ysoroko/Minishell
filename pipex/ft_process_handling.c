/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 16:24:12 by ablondel          #+#    #+#             */
/*   Updated: 2021/06/29 17:51:03 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_child_one(t_pipex *add)
{
	add->i = 0;
	add->file1 = open(add->infile, O_RDONLY);
	if (add->file1 == -1)
		return (NULL);
	if ((dup2(add->file1, 0) == -1) || (dup2(add->pfd[1], 1) == -1))
		return (NULL);
	close(add->file1);
	close(add->pfd[0]);
	close(add->pfd[1]);
	add->tmp = NULL;
	while (add->paths[add->i])
	{
		add->tmp = ft_strjoin(add->paths[add->i], add->args1[0]);
		if (!add->tmp)
			exit(EXIT_FAILURE);
		if (execve(add->tmp, add->args1, NULL) != -1)
			exit(EXIT_SUCCESS);
		add->i++;
	}
	return ("YEEEEEH!");
}

char	*ft_child_two(t_pipex *add)
{
	add->i = 0;
	add->res = 1;
	add->file2 = open(add->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (add->file2 == -1)
		return (NULL);
	if ((dup2(add->file2, 1) == -1) || (dup2(add->pfd[0], 0) == -1))
		return (NULL);
	close(add->file2);
	close(add->pfd[0]);
	close(add->pfd[1]);
	add->tmp = NULL;
	while (add->paths[add->i])
	{
		add->tmp = ft_strjoin(add->paths[add->i], add->args2[0]);
		if (!add->tmp)
			exit(EXIT_FAILURE);
		if (execve(add->tmp, add->args2, NULL) != -1)
			exit(EXIT_SUCCESS);
		add->i++;
	}
	return ("YEEEEEH!");
}

void	ft_parent(t_pipex *add)
{
	if (add->s != NULL)
		free(add->s);
	if (add->paths != NULL)
		ft_free_tab(add->paths);
	if (add->tmp != NULL)
		free(add->tmp);
	if (add->args1 != NULL)
		ft_free_tab(add->args1);
	if (add->args2 != NULL)
		ft_free_tab(add->args2);
	close(add->pfd[0]);
	close(add->pfd[1]);
	wait(&add->p1);
	wait(&add->p2);
}
