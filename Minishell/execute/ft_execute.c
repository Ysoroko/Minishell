/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 17:46:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/16 16:42:45 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** FT_EXECUTE
** This function is the main bridge between parsing and executing commands
** It takes the parsing as a t_list* structure, passes it to a different
** function which will execute all the commands for every element of 
** the t_list* structure
*/

void	ft_print_tab(char **tab)
{
	int i = 0;

	if (!tab)
		printf("NO DATA\n");
	else
		while (tab[i])
			printf("___|%s|___\n", tab[i++]);
	printf("\n");
}

void	ft_print_cmd_table(t_command *cmd)
{
	printf("-------------------------------------------------\n");
	printf("[EXECVE]\n");
	ft_print_tab(cmd->str_tab_for_execve);
	printf("type in = [%d]\n", cmd->redir_type_in);
	printf("type out = [%d]\n", cmd->redir_type_out);
	printf("infile = [%s]\n", cmd->infile);
	printf("outfile = [%s]\n", cmd->outfile);
	printf("is piped = [%d]\n", cmd->is_piped);
}

void	ft_execute(t_dl_lst *command_list)
{
	t_command *cmd;
	int	npipes = ft_lstsize((t_list *)command_list);
	int pfd[2 * npipes];
	pid_t p;
	int status;
	int i = 0;
	int j = 0;

	if (!command_list)
		return ;
	ft_dl_lstiter(command_list, ft_print_command_list);
	while (i < npipes)
	{
		if (pipe(pfd + i * 2) < 0)
		{
			printf("Pipe error.\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (command_list)
	{
		cmd = (t_command *)command_list->content;
		p = fork();
		//ft_print_cmd_table(cmd);
		if (p == 0)
		{
			if (cmd->infile)
			{
				cmd->fdin = open(cmd->infile, O_RDONLY);
				dup2(cmd->fdin, 0);
				close(cmd->fdin);
			}
			if (cmd->outfile)
			{
				if (cmd->redir_type_out == 1)
					cmd->fdout = open(cmd->outfile, O_RDWR | O_CREAT | O_TRUNC, 0777);
				else
					cmd->fdout = open(cmd->outfile, O_RDWR | O_CREAT | O_APPEND, 0777);
				dup2(cmd->fdout, 1);
				close(cmd->fdout);
			}
			if (command_list->next)
			{
				if (!cmd->outfile)
					dup2(pfd[j + 1], 1);
			}
			if (j != 0 && j != 2 * npipes)
			{
				if (!cmd->infile)
					dup2(pfd[j - 2], 0);
			}
			i = 0;
			while (i < 2 * npipes)
			{
				close(pfd[i]);
				i++;
			}
			execve(cmd->str_tab_for_execve[0], cmd->str_tab_for_execve, NULL);
		}
		command_list = command_list->next;
		j += 2;
	}
	i = 0;
	while (i < 2 * npipes)
	{
		close(pfd[i]);
		i++;
	}
	i = 0;
	while (i < npipes + 1)
	{
		wait(&status);
		i++;
	}
}
