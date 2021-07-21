/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 11:32:44 by ablondel          #+#    #+#             */
/*   Updated: 2021/07/21 12:10:54 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_wsp(char c)
{
	return (c == '\v' || c == '\r' || c == '\t'
			|| c == '\f' || c == '\n' || c == ' ');
}

int	ft_sep(char c, char *sep)
{
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_count_words(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	if (ft_wsp(s[0]))
		n = 0;
	while (s[i])
	{
		if (ft_wsp(s[i - 1]) && !ft_wsp(s[i]) && s[i] != '\0')
			n++;
		i++;
	}
	return (n);
}

int	ft_count_pipes(char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s == '|')
			n++;
		s++;
	}
	return (n);
}

char	**ft_split_pipes(t_msh *add, char *line)
{
	add->i = -1;
	add->j = 0;
	add->k = 0;
	add->pipes = NULL;
	add->pipes = (char **)malloc(sizeof(char *) * (ft_count_pipes(line) + 1));
	if (!add->pipes)
		return (NULL);
	while (++add->i <= ft_count_pipes(line))
	{
		add->pipes[add->i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
		if (!add->pipes[add->i])
			return (NULL); // ++ free tab
		while (line[add->j] && line[add->j] == '|')
			add->j++;
		while (line[add->j] && line[add->j] != '|')
			add->pipes[add->i][add->k++] = line[add->j++];
		add->pipes[add->i][add->k] = '\0';
		add->k = 0;
	}
	add->pipes[add->i] = NULL;
	return (add->pipes);
}

int	main(int ac, char **av, char **env)
{
	t_msh add;
	char *line;
	int i = 0;
	char **pipes = NULL;

	while (1)
	{
		line = readline("MINISHELL: ");
		printf("line = {%s}\n", line);
		printf(">>words	%d\n", ft_count_words(line));
		printf(">>pipes	%d\n", ft_count_pipes(line));
		pipes = ft_split_pipes(&add, line);
		while (add.pipes[i])
		{
			printf("[%s]\n", add.pipes[i]);
			i++;
		}
		printf("[%s]\n", add.pipes[i]);
		add_history(line);
		if (!line)
			return (0);
	}
}