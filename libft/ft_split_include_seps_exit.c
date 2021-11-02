/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_include_seps_exit.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 09:48:32 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/17 14:19:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/*
** int	ft_spaces_only(char *str, char *seps)
** This function is used to check if the separator part we have in front of
** us only consists of spaces.
** Returns 1 if yes, 0 if no and other characters from "seps" are encountered
*/

//static int	ft_spaces_only(char *str, char *seps)
//{
//	int	i;
//
//	i = -1;
//	while (str[++i])
//	{
//		if (!ft_isspace(str[i]) && ft_strchr(seps, str[i]))
//			return (0);
//		if (!ft_isspace(str[i]) && !ft_strchr(seps, str[i]))
//			return (1);
//	}
//	return (1);
//}

/*
** static int	ft_wordcount(char const *str, char *seps)
** This function is used to calculate how many strings we will have
** in our final string array.
** Returns the number of words.
*/

static int	ft_wordcount(char const *str, char *seps)
{
	int	i;
	int	count;

	if (!str || !str[0])
		return (0);
	i = 1;
	count = 1;
	while (str[i])
	{
		if (!ft_strchr_nq(str, i, seps) && ft_strchr_nq(str, i - 1, seps))
			count++;
		else if (ft_strchr_nq(str, i, seps) && !ft_strchr_nq(str, i - 1, seps))
			count++;
		i++;
	}
	return (count);
}

/*
** char	**ft_malloc_str_tab_exit(char const *str, char *seps)
** This function is used to malloc the string array
** ft_split will return.
** In case of malloc error it will exit the program straight away.
*/

static char	**ft_malloc_str_tab_exit(char const *str, char *seps)
{
	int		len;
	char	**tab_str;

	if (!str)
		return (0);
	len = ft_wordcount(str, seps);
	tab_str = malloc(sizeof(*tab_str) * (len + 1));
	if (!tab_str)
		exit(EXIT_FAILURE);
	return (tab_str);
}

static int	ft_next_word_count(char const *str, char *sep, int i)
{
	int	count;

	count = 0;
	if (!ft_strchr_nq(str, i, sep))
	{
		while (str[i] && !ft_strchr_nq(str, i, sep))
		{
			count++;
			i++;
		}
	}
	else
	{
		while (str[i] && ft_strchr_nq(str, i, sep))
		{
			count++;
			i++;
		}
	}
	return (count);
}

/*
** char	**ft_split_seps_included(char const *str, char charset)
** This function will create an array of strings where every string
** is delimited by the separators, but it will also include the separators
** Example: ft_split_seps_included("echo bonjour>>test.txt< test2.txt", " ><")
** Returs an array str_arr such as: 
** str_arr[0] = "echo"
** str_arr[1] = " "
** str_arr[2] = "bonjour"
** str_arr[3] = ">>"
** str_arr[4] = "test.txt"
** str_arr[5] = "< "
** str_arr[6] = test2.txt
** str_arr[7] = NULL
*/

/// Useless function to respect the norm and get less lines
static void	ft_initialize_variables(int *s, int *i)
{
	*s = 0;
	*i = -1;
}

// < infile wc -l | ls -la > outfile
char	**ft_split_seps_included_exit(char const *str, char *seps)
{
	int		s;
	int		i;
	int		j;
	char	**tab_str;

	ft_initialize_variables(&s, &i);
	tab_str = ft_malloc_str_tab_exit(str, seps);
	while (++i < ft_wordcount(str, seps))
	{
		j = 0;
		tab_str[i] = ft_malloc_exit(ft_next_word_count(str, seps, s) + 1);
		if (!ft_strchr_nq(str, s, seps))
		{
			while (str[s] && !ft_strchr_nq(str, s, seps))
				tab_str[i][j++] = str[s++];
		}
		else if (ft_strchr_nq(str, s, seps))
		{
			while (str[s] && ft_strchr_nq(str, s, seps))
				tab_str[i][j++] = str[s++];
		}
		tab_str[i][j] = '\0';
	}
	tab_str[i] = 0;
	return (tab_str);
}
