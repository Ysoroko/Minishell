/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:32:44 by ablondel          #+#    #+#             */
/*   Updated: 2021/07/22 17:40:29 by ablondel         ###   ########.fr       */
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
	n = 0;
	if (!check_set(s[0], set))
		n = 1;
	while (s[i])
	{
		if ((check_set(s[i - 1], set) && !check_set(s[i], set)) && s[i] != '\0')
			n++;
		i++;
	}
	return (n);
}

int	ft_count_pipes(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '|')
			n++;
		i++;
	}
	return (n);
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

int	allocate(t_msh *add, char *s, char *set)
{
	add->limit = 0;
	if (add->c == ' ')
		add->limit = ft_count_words(s, set) + 1;
	else if (add->c == ':')
		add->limit = ft_count_env(s) + 1;
	else
		add->limit = ft_count_pipes(s) + 1;
	return (add->limit);
}

char	**ft_split(t_msh *add, char *s, char *set, char **dst)
{
	add->i = -1;
	add->j = 0;
	add->k = 0;
	add->limit = allocate(add, s, set);
	dst = malloc(sizeof(char *) * (add->limit + 1));
	if (!dst)
		return (NULL);
	if (add->c == ' ')
		add->limit -= 1;
	while (++add->i < add->limit)
	{
		dst[add->i] = malloc(sizeof(char) * (ft_strlen(s) + 2));
		if (!dst[add->i])
			return (ft_free_tab(dst));
		while (s[add->j] && check_set(s[add->j], set))
			add->j++;
		while (s[add->j] && !check_set(s[add->j], set))
			dst[add->i][add->k++] = s[add->j++];
		close_line(add, add->c, dst);
		if (add->c == ':')
		{
			dst[add->i][add->k] = '/';
			dst[add->i][add->k + 1] = '\0';
		}
		else
			dst[add->i][add->k] = '\0';
		add->k = 0;
	}
	dst[add->i] = NULL;
	return (dst);
}

int	file_exec_check(t_msh *add, char *file, int i, int j)
{
	int k = 0;
	DIR	*dir;
	struct dirent *p;

	while (add->paths[k])
	{
		dir = opendir(add->paths[k]);
		while ((p = readdir(dir)) != NULL)
		{
			if (strcmp(file, p->d_name) == 0)
			{
				printf("\033[0;32m");
				printf("\n{%s} exists in the directory {%s} as: [%s]\n", file, add->paths[k], ft_strjoin(add->paths[k], file));
				if (add->types[i][j] == NONE)
					add->types[i][j] = EXECUTABLE;
				printf("\033[0;37m");
				return (1);
			}
		}
		closedir(dir);
		k++;
	}
	printf("\033[0;31m");
	//printf("\n{%s} does not exists in any directory specified by the PATH variable\n", file);
	printf("\033[0;37m");
	return (-1);
}

int	file_type_check(t_msh *add, char *file, int i, int j)
{
	struct stat sb;
	file_exec_check(add, file, i, j);
	if(add->types[i][j] == NONE)
	{
	if (stat(file, &sb) == 0)
	{
		printf("\033[4;32m");
		printf("\n	file {%s} exists.\n", file);
		printf("\033[0;37m");
		if (stat(file, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			printf("\n		file {%s} is an executable.\n", file);
			if (add->types[i][j] == NONE)
				add->types[i][j] = EXECUTABLE;
		}
		else
		{
			printf("\n		file {%s} is not an executable.\n", file);
		}
		if (stat(file, &sb) == 0 && sb.st_mode & S_IRUSR)
		{
			printf("		file {%s} is readable.\n", file);
			if (add->types[i][j] == NONE)
				add->types[i][j] = READABLE;
		}
		else
		{
			printf("		file {%s} is not readable.\n", file);
			if (add->types[i][j] == NONE)
				add->types[i][j] = ARGUMENT;
		}
		if (stat(file, &sb) == 0 && sb.st_mode & S_IWUSR)
		{
			printf("		file {%s} is writable.\n\n\n", file);
			if (add->types[i][j] == NONE)
				add->types[i][j] = WRITABLE;
			if (add->types[i][j] == READABLE)
				add->types[i][j] = PERMITTED;
		}
		else
		{
			printf("		file {%s} is not writable.\n\n\n", file);
			if (add->types[i][j] == NONE)
				add->types[i][j] = ARGUMENT;
		}
	}
	else if (stat(file, &sb) == -1)
	{
		printf("\033[4;31m");
		if (add->types[i][j] == NONE)
			add->types[i][j] = KEYWORD;
		if (add->types[i][j] == NONE)
			printf("\n	file {%s} does not exist.\n", file);
		printf("\033[0;37m");
	}
	}
	return (0);
}

int	ft_strslen(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

int		tests(t_msh *add, int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	int i = 0;
	int j = 0;
	char *line = "< infile ls -l | wc -a -l -w > outfile | cat |echo -n \"bonjour\" | grep 'line' >> outfile | a.out ";
	add->c = '|';
	add->strs = ft_split(add, line, "|", add->strs);
	printf("number of lines in the line = {%d}\n", ft_strslen(add->strs));
	add->types = malloc(sizeof(int *) * (ft_strslen(add->strs)));
	printf("\n\n\n\n");
	while (add->strs[i] != 0)
	{
		add->c = ' ';
		add->piped = NULL;
		add->piped = ft_split(add, add->strs[i], "\v\r\t\f\n ", add->piped);
		add->types[i] = malloc(sizeof(int *) * (ft_strslen(add->piped)));
		while (add->piped[j])
		{
			printf("---------------------------------------------------------------------words in the pipe are : %s \n\n\n", add->strs[i]);
			//printf("\n\nlen of the piped line = {%d}\n", ft_strslen(add->piped));
			add->types[i][j] = NONE;
			printf("---[%s]\n", add->piped[j]);
			if (add->piped[j][0] == '-' && ((add->piped[j][1] >= 'A' && add->piped[j][1] <= 'Z') || (add->piped[j][1] >= 'a' && add->piped[j][1] <= 'z')))
				if (add->types[i][j] == NONE)
					add->types[i][j] = OPTION;
			if (add->piped[j][0] == '<' && !add->piped[j][1])
				if (add->types[i][j] == NONE)
					add->types[i][j] = RLSIMPLE;
			if (add->piped[j][0] == '>' && !add->piped[j][1])
				if (add->types[i][j] == NONE)
					add->types[i][j] = RRSIMPLE;
			if (add->piped[j][0] == '<' && add->piped[j][1] == '<')
				if (add->types[i][j] == NONE)
					add->types[i][j] = RLDOUBLE;
			if (add->piped[j][0] == '>' && add->piped[j][1] == '>')
				if (add->types[i][j] == NONE)
					add->types[i][j] = RRDOUBLE;
			file_type_check(add, add->piped[j], i, j);
			printf("\n   TYPE OF WORD\n[[\t%d\t]]\n\n\n", add->types[i][j]);
			j++;
		}
		j = 0;
		i++;
	}
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_msh add;
	char	*all_paths;
	char	**paths;

	all_paths = NULL;
	paths = NULL;
	all_paths = ft_get_paths(env);
	add.c = ':';
	add.paths = ft_split(&add, all_paths, ":", add.paths);
	tests(&add, ac, av, env);
	ft_free_tab(add.paths);
	ft_free_tab(add.strs);
	return (0);
}
