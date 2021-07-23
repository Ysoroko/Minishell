/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoted_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:03:28 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/19 15:10:32 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** ft_double_quotes_copy
** This function is responsible for double quotes copy
** Double quotes will:
** 1) Apply '\' character as an escape character but only if it is followed by:
** ‘$’, ‘`’, ‘"’, ‘\’, or newline
** 2) Replace env var names starting with '$' by their values
** 3) Simply copy characters in the rest of the cases
** This function will append the applied quotes to *dest and modify
** the values of *i and *j accordingly
*/

static void	ft_double_quotes_copy(char *str, char **dest, int *i, int *j)
{
	int	k;
	int	l;

	k = 1;
	while (str[k] && str[k] != '\"')
	{
		if (str[k] == '$')
		{
			//printf("appending in ft_dq_copy at\n \t&str[k]: [%s]\n \tk: [%d]\n, \t*dest: [%s]\n", &(str[k]), k, *dest);
			ft_append_env_var_value(&(str[k]), dest, &k, j);
			//printf("after appending in ft_dq_copy at\n \t&str[k]: [%s]\n \tk: [%d]\n, \t*dest: [%s]\n", &(str[k]), k, *dest);
		}
		else
		{
			printf("copying in ft_dq_copy [%c] to dest at j:[%d]\n", str[k], *j);
			(*dest)[*j] = str[k];
		}
		(*j)++;
		k++;
	}
	if (!(*dest)[*j])
		(*j)--;
	*i += k;
	//printf("str[i] at the end of ft_dq_cpy: [%c]\n", str[*i]);
}

/*
** ft_single_quotes_copy
** This function is responsible for single quotes copy
** Single quotes take the litteral value of everthing encountered between the
** quotes
** Example: '$TERM\"' --> $TERM\"
*/

static void	ft_single_quotes_copy(char *str, char **dest, int *i, int *j)
{
	int	k;

	k = 1;
	while (str[k] && str[k] != '\'')
	{
		(*dest)[*j] = str[k];
		k++;
		(*j)++;
	}
	*i += k;
}

/*
** ft_quoted_copy
** This function is the central hub of the quoted copying
** str is the argument starting with a quote (single or double)
** (if str is the whole string it's actually &(str[*i]))
** *dest is the string where we will write the applied quotes
** and *i is current position in str / *j in *dest
** It will append the apllied quotes at the end of *dest
** and modify the values of *i and *j respectively
*/

void	ft_quoted_copy(char *str, char **dest, int *i, int *j)
{
	char	quote;

	if (!str || !dest || !*dest || !i || !j)
		return ;
	quote = str[0];
	if (quote == '\'')
	{
		ft_single_quotes_copy(str, dest, i, j);
	}
	else if (quote == '\"')
	{
		ft_double_quotes_copy(str, dest, i, j);
	}
	//printf("dest at the end of quoted copy: [%s]\n", *dest);
}
