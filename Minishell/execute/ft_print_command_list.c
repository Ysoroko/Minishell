/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_command_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 14:41:39 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/23 17:31:42 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** char	*ft_role_color(int m)
** This function is used to determine the color for printing
** based on the corresponding value in macros_tab in our t_command structure
** Returns the string containing the color
*/

static char	*ft_role_color(int m)
{
	if (m == ERROR)
		return (BOLDRED);
	else if (m == COMMAND)
		return (BOLDGREEN);
	else if (m == FLAG)
		return (BOLDWHITE);
	else if (m == COMMAND_ARG)
		return (BOLDCYAN);
	else if (m == REDIR_L || m == REDIR_LL || m == REDIR_R || m == REDIR_RR)
		return (BOLDMAGENTA);
	else if (m == REDIR_ARG || m == R_REDIR_ARG || m == RR_REDIR_ARG
		|| m == L_REDIR_ARG || m == LL_REDIR_ARG)
		return (BOLDBLUE);
	else if (m == PIPE)
		return (BOLDYELLOW);
	else
		return (BOLDRED);
}

/*
** char	*ft_role_str(int m)
** This function is used to determine the string for printing
** based on the corresponding value in macros_tab in our t_command structure
** Returns the corresponding string
*/

static char	*ft_role_str(int m)
{
	const char	*tab[] = {"ERROR", "REDIR_R", "REDIR_RR", "REDIR_L",
					"REDIR_LL", "REDIR_ARG", "PIPE", "COMMAND", "FLAG",
					"COMMAND_ARG", "R_REDIR_ARG", "L_REDIR_ARG",
					"RR_REDIR_ARG", "LL_REDIR_ARG"};

	if (m > ft_str_tab_len((char **)tab) || m < 0)
		return ("Undefined");
	else
		return ((char *)(tab[m]));
}

/*
** void	ft_print_tab_header(int	s)
** This function simply prints the header of the tab which will be like:
** ____________________________________________________________
** i        | Str_tab_all      | Macros tab       | Execve_tab 
** ____________________________________________________________
*/

static void	ft_print_tab_header(int s)
{
	printf(BOLDWHITE);
	ft_print_line_of_chars('_', LINE_LENGTH);
	printf("\n%*s | %*s | %*s | %*s\n", PLACE_FOR_I, "i", s, "str_tab_all", s,
		"role_macros", s, "str_tab_for_execve");
	ft_print_line_of_chars('_', LINE_LENGTH);
	printf("\n");
	printf(COLOR_RESET);
}

/*
** char	*ft_print_execve_tab(char **tab, int i)
** This function allows us to print execve_tab next to str_tab_all and macros
** despite execve_tab usually being shorter than those 2.
** It simply returns the execve_tab[i] element if element i exists
** or an empty string otherwise
*/

static char	*ft_print_execve_element(char **tab, int i)
{
	int	len;

	len = ft_str_tab_len(tab);
	if (i >= len)
		return ("");
	else
		return (tab[i]);
}

int	ft_check_file_permissions(char *filename)
{
	struct stat	sb;

	if (!filename)
		return (-1);
	if (stat(filename, &sb) == 0)
	{
		if (sb.st_mode & S_IRUSR && sb.st_mode & S_IWUSR)
			return (1);
		else if (sb.st_mode & S_IWUSR)
			return (2);
		else if (sb.st_mode & S_IRUSR)
			return (3);
		return (0);
	}
	return (-1);
}

void	ft_hdoc(t_command *cmd)
{
	int	fd;

	if (ft_check_file_permissions("hdoc/tmp") >= 1)
		fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_TRUNC, 0664);
	else
		fd = open("hdoc/tmp", O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (1)
	{
		cmd->buffer = readline("> ");
		if (ft_strcmp(cmd->buffer, cmd->keyword[cmd->keyword_index]) == 0)
		{
			if (close(fd) == -1)
				exit(EXIT_FAILURE);
			return ;
		}
		write(fd, cmd->buffer, ft_strlen(cmd->buffer));
		write(fd, "\n", 1);
	}
	if (close(fd) == -1)
		exit(EXIT_FAILURE);
}

void	ft_add_redir_out(t_command *cmd, int m, int i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->str_tab_all[i + 1] != NULL)
		cmd->outfile = ft_strdup(cmd->str_tab_all[i + 1]);
	else
		exit(EXIT_FAILURE);
	if (!cmd->outfile)
		exit(EXIT_FAILURE);
	if (m == REDIR_R)
	{
		cmd->fdout = open(cmd->outfile, O_CREAT | O_TRUNC, 0664);
		cmd->redir_type_out = 1;
	}
	else
	{
		cmd->fdout = open(cmd->outfile, O_CREAT | O_APPEND, 0664);
		cmd->redir_type_out = 2;
	}
	if (cmd->fdout == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (close(cmd->fdout) == -1)
		exit(EXIT_FAILURE);
}

void	ft_add_redir_in(t_command *cmd, int m, int i)
{
	cmd->redir_type_in = 3;
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->str_tab_all[i + 1] != NULL)
		cmd->infile = ft_strdup(cmd->str_tab_all[i + 1]);
	else
		exit(EXIT_FAILURE);
	if (!cmd->infile)
		exit(EXIT_FAILURE);
	cmd->fdin = open(cmd->infile, O_RDONLY);
	if (cmd->fdin == -1)
		exit(EXIT_FAILURE);
	if (close(cmd->fdin) == -1)
		exit(EXIT_FAILURE);
}

void	ft_add_redir_hdoc(t_command *cmd, int m, int i)
{
	cmd->redir_type_in = 4;
	if (cmd->str_tab_all[i + 1] != NULL)
		cmd->keyword[cmd->keyword_index] = ft_strdup(cmd->str_tab_all[i + 1]);
	else
		exit(EXIT_FAILURE);
	if (!cmd->keyword[cmd->keyword_index])
		exit(EXIT_FAILURE);
	ft_hdoc(cmd);
	cmd->keyword_index++;
	cmd->keyword[cmd->keyword_index] = 0;
}

void	ft_add_redir_file(t_command *cmd, int m, int i)
{
	if (m == REDIR_R || m == REDIR_RR)
		ft_add_redir_out(cmd, m, i);
	else if (m == REDIR_L || m == REDIR_LL)
	{
		if (m == REDIR_L)
			ft_add_redir_in(cmd, m, i);
		else if (m == REDIR_LL)
			ft_add_redir_hdoc(cmd, m, i);
	}
	return ;
}

/*
** FT_PRINT_COMMAND_LIST
** A debugging function used to print the list of our commands and related
** flags/arguments/redirections to make sure everything is running smoothly
*/

int	ft_exec_check(char *path, char *cmd)
{
	int				i;
	DIR				*dir;
	struct dirent	*d;
	char			*tmp;

	i = 0;
	dir = opendir(path);
	d = readdir(dir);
	while (d != NULL)
	{
		if (strcmp(cmd, d->d_name) == 0)
			return (1);
		d = readdir(dir);
	}
	closedir(dir);
	return (-1);
}

int	ft_set_paths(char **exec_name)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = -1;
	tmp = getenv("PATH");
	if (!tmp)
		return (-1);
	paths = ft_split(tmp, ':');
	if (!paths)
		return (-1);
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin_exit(paths[i], "/");
		free(tmp);
		if (ft_exec_check(paths[i], *exec_name) == 1)
		{
			tmp = *exec_name;
			*exec_name = ft_strjoin_exit(paths[i], *exec_name);
			free(tmp);
			return (1);
		}
	}
	return (0);
}

int	ft_check_binary(char *filename)
{
	struct stat	sb;

	if (!filename || !filename[0])
		return (-1);
	if (stat(filename, &sb) == 0)
	{
		if (sb.st_mode & S_IXUSR)
			return (1);
	}
	return (-1);
}

void	ft_print_command_list(void *current_command)
{
	t_command	*command;
	int			m;
	int			i;

	i = -1;
	command = (t_command *)(current_command);
	if (!command || !command->str_tab_all || !command->str_tab_all[0]
		|| !command->str_tab_for_execve || ! command->str_tab_for_execve[0]
		|| !command->role_macros || !command->role_macros[0])
	{
		return ;
	}
	command->keyword = (char **)malloc(sizeof(char *) * 1024);
	if (!command->keyword)
		exit(EXIT_FAILURE);
	command->keyword_index = 0;
	while (command->str_tab_all[++i])
	{
		m = (command->role_macros)[i];
		if (ft_is_a_redir_arg_macro(m))
			ft_add_redir_file(command, m, i);
	}
	if (ft_check_binary(command->str_tab_for_execve[0]) != 1)
	{
		if (ft_set_paths(&command->str_tab_for_execve[0]) == -1)
			exit(EXIT_FAILURE);
	}
}
