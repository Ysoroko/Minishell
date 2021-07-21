/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:32:44 by ablondel          #+#    #+#             */
/*   Updated: 2021/07/21 19:44:13 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_memzero(unsigned int len)
{
	char	*dst;

	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (len)
		dst[--len] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char			*dst;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	dst = ft_memzero(ft_strlen(s1) + ft_strlen(s2));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}

int	ft_count_env(char *s)
{
	int	n;

	n = 1;
	while (*s)
	{
		if (*s == ':')
			n++;
		s++;
	}
	return (n);
}

int		ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (s1[i] && s2[i] && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_dup_path(char *path)
{
	char *dst;
	int i;
	int len;

	dst = NULL;
	i = -1;
	len = 0;
	while (path[len])
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (path[++i])
		dst[i] = path[i];
	dst[i] = '\0';
	return (dst);
}

char	*ft_get_paths(char **env)
{
	unsigned int i;
	char	*dst;

	i = 0;
	dst = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 4) == 0)
		{
			dst = ft_dup_path(env[i] + 5);
			if (!dst)
				return (NULL);
		}
		i++;
	}
	return (dst);
}

int	check_set(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

int	ft_count_words(char *s, char *set)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (s[i])
	{
		if (check_set(s[i - 1], set) && !check_set(s[i], set))
			n++;
		i++;
	}
	return (n);
}

char	**allocate(t_msh *add, char *s, char *set, char **dst)
{
	add->i = -1;
	add->j = 0;
	add->k = 0;
	add->limit = 0;
	dst = NULL;
	if (add->c == ' ')
		add->limit = ft_count_words(s, set) + 1;
	else if (add->c == ':')
		add->limit = ft_count_env(s) + 1;
	dst = (char **)malloc(sizeof(char *) * add->limit);
	if (!dst)
		return (0);
	return (dst);
}

void	close_line(t_msh *add, char c, char **dst)
{
	if (c == ':')
	{
		dst[add->i][add->k] = '/';
		dst[add->i][add->k + 1] = '\0';
	}
	else
		dst[add->i][add->k] = '\0';
	add->k = 0;
}

char	**ft_free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	while (--i >= 0)
		free(tab[i]);
	free(tab);
	tab = NULL;
	return (tab);
}

char	**ft_split(t_msh *add, char *s, char *set, char **dst)
{
	dst = allocate(add, s, set, dst);
	if (!dst)
		return (NULL);
	while (++add->i < add->limit)
	{
		dst[add->i] = (char *)malloc(sizeof(char) * 1024);
		if (!dst[add->i])
			return (ft_free_tab(dst));
		while (s[add->j] && check_set(s[add->j], set))
			add->j++;
		while (s[add->j] && !check_set(s[add->j], set))
			dst[add->i][add->k++] = s[add->j++];
		close_line(add, add->c, dst);
	}
	dst[add->i] = NULL;
	return (dst);
}

int	file_exec_check(t_msh *add, char *file)
{
	int i = 0;
	DIR	*dir;
	struct dirent *p;

	if (!file)
		return (-1);
	while (add->paths[i])
	{
		dir = opendir(add->paths[i]);
		while ((p = readdir(dir)) != NULL)
		{
			if (strcmp(file, p->d_name) == 0)
			{
				printf("\033[0;32m");
				printf("\n{%s} exists in the directory {%s} as: [%s]\n", file, add->paths[i], ft_strjoin(add->paths[i], file));
				printf("\033[0;37m");
				return (1);
			}
		}
		closedir(dir);
		i++;
	}
	printf("\033[0;31m");
	printf("\n{%s} does not exists in any directory specified by the PATH variable\n", file);
	printf("\033[0;37m");
	return (-1);
}

int	file_type_check(t_msh *add, char *file)
{
	struct stat sb;
	file_exec_check(add, file);
	if (stat(file, &sb) == 0)
	{
		printf("\033[4;32m");
		printf("\n	file {%s} exists.\n", file);
		printf("\033[0;37m");
	}
	else if (stat(file, &sb) == -1)
	{
		printf("\033[4;31m");
		printf("\n	file {%s} does not exist.\n", file);
		printf("\033[0;37m");
	}
	if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		printf("\n		file {%s} is an executable.\n", file);
	else
		printf("\n		file {%s} is not an executable.\n", file);
	if (stat(file, &sb) == 0 && sb.st_mode & S_IRUSR)
		printf("		file {%s} is readable.\n", file);
	else
		printf("		file {%s} is not readable.\n", file);
	if (stat(file, &sb) == 0 && sb.st_mode & S_IWUSR)
		printf("		file {%s} is writable.\n\n\n", file);
	else
		printf("		file {%s} is not writable.\n\n\n", file);
	return (0);
}

int		tests(t_msh *add, int ac, char **av, char **env)
{
	int i = 0;
	char *line = "< infile ls -l |		wc -al > outfile | echo -n bonjour | grep line >> outfile | a.out";
	add->c = ' ';
	add->strs = ft_split(add, line, "\v\r\t\f\n ", add->strs);
	printf("\n\n\n\n");
	printf("----------------------------------------------------------------------\n");
	while (add->strs[i])
	{
		if (ft_strlen(add->strs[i]) == 1 || ft_strlen(add->strs[i]) == 2)
		{
			if (add->strs[i][0] == '|')
			{printf("\033[0;33m");
				printf("\n{%s} is a pipe", add->strs[i]);
				//printf("This section will have to manage all input generated by the previous\n");
				//printf("commands and transmit it to the command after that pipe. Theses lines\n");
				//printf("will be used as input for the command that comes after the delimiter.\n\n");
			}printf("\033[0;37m");
			if (add->strs[i][0] == '<' && !add->strs[i][1])
			{printf("\033[0;36m");
				printf("\n{%s} is an input redirection", add->strs[i]);
				//printf("This section will have to check if the next word is a file and, if it is,\n");
				//printf("take input from that file (dup2(fd, STDIN)) and display the result of the command.");
				//printf("If no file is specified the rediretion will take input from STDIN and display the result.\n\n");
			}printf("\033[0;37m");
			if (add->strs[i][0] == '<' && add->strs[i][1] == '<')
			{printf("\033[0;36m");
				printf("\n{%s} is a here_doc redirection", add->strs[i]);
				//printf("This section will have to save the next word as delimiter for the end of reading\n");
				//printf("then read the input from STDIN and save all the lines until the word is found.\n");
				//printf("The saved lines will be used as input for the command following that delimiter\n\n");
			}printf("\033[0;37m");
			if (add->strs[i][0] == '>' && !add->strs[i][1])
			{printf("\033[0;36m");
				printf("\n{%s} is a TRUNC output redirection", add->strs[i]);
				//printf("If a filename is specified, this redirection will output the result of the command\n");
				//printf("in said file after setting the file to 0 size. all data inside the file will be truncated\n");
				//printf("and the new output will replace it. If the file does not exists it will be created. If the\n");
				//printf("file exists but the permissions are unsufficient, an error will be returned.\n\n");
			}printf("\033[0;37m");
			if (add->strs[i][0] == '>' && add->strs[i][1] == '>')
			{printf("\033[0;36m");
				printf("\n{%s} is an APPEND output redirection", add->strs[i]);
				//printf("If a filename is specified, this redirection will output the result of the command\n");
				//printf("in said file appended after the last byte of data. If the file does not exists it will be created.\n");
				//printf("If the file exists but the permissions are unsufficient, an error will be returned.\n\n");
			}printf("\033[0;37m");
		}
		if (add->strs[i][0] == '-' && ((add->strs[i][1] >= 'A' && add->strs[i][1] <= 'Z') || (add->strs[i][1] >= 'a' && add->strs[i][1] <= 'z')))
		{printf("\033[0;34m");
			printf("\n{%s} is an option/keyword to the previous command {%s}", add->strs[i], add->strs[i - 1]);
			//printf("This option has to be saved in a char** for execve.\n\n");
		}printf("\033[0;37m");
		file_type_check(add, add->strs[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_msh add;
	char	*all_paths;
	char	**paths;
	int i = 0;

	all_paths = NULL;
	paths = NULL;
	add.c = ':';
	all_paths = ft_get_paths(env);
	add.paths = ft_split(&add, all_paths, ":", add.paths);
	tests(&add, ac, av, env);
	ft_free_tab(add.paths);
	ft_free_tab(add.strs);	
	return (0);
}
