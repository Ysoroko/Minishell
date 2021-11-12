/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes_and_env_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/12 15:01:04 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** void	ft_initialize_variables(char **str, int *i, int *j, char **ret)
** This function is used to initialize variables and save lines in the main fct
*/

static void	ft_initialize_variables(char **str, int *i, int *j, char **ret)
{
	*i = -1;
	*j = 0;
	*ret = ft_calloc_exit(ft_calculate_total_length_needed(*str) + 1, 1);
}

/*
**
*/

static void	ft_apply_conditions(char **str, int *i, int *j, char **ret)
{
	if (ft_isspace((*str)[*i]))
		ft_copy_spaces(&((*str)[*i]), ret, i, j);
	else if ((*str)[*i] == '$' && ft_is_env_name_char((*str)[(*i) + 1]))
		ft_append_env_var_value(&((*str)[*i]), ret, i, j);
	else if ((*str)[*i] == '$' && ((*str)[(*i) + 1] == '\''
			|| (*str)[(*i) + 1] == '\"'))
		;
	else if (ft_char_is_a_start_quote((*str), *i))
		ft_quoted_copy(&((*str)[*i]), ret, i, j);
	else
		(*ret)[*j] = (*str)[*i];
}

static void	ft_apply_env_conditions(char **str, int *i, int *j, char **ret)
{
	char	c;
	int		quoted;
	char	next_char;

	quoted = 0;
	c = (*str)[*i];
	if (c == '$')
	{
		quoted = ft_char_between_the_quotes(*i, *str);
		next_char = (*str)[(*i) + 1];
	}
	if ((*str)[*i] == '$' && ft_is_env_name_char(next_char) && quoted != '\'')
		ft_append_env_var_value(&((*str)[*i]), ret, i, j);
	else if ((*str)[*i] == '$' && ((*str)[(*i) + 1] == '\''
			|| (*str)[(*i) + 1] == '\"'))
		;
	else
		(*ret)[*j] = (*str)[*i];
}

char	*ft_apply_env_vars(char **str)
{
	int		i;
	int		j;
	char	*ret;

	if (!str || !(*str))
		return (0);
	ft_initialize_variables(str, &i, &j, &ret);
	while ((*str)[++i])
	{
		ft_apply_env_conditions(str, &i, &j, &ret);
		if (ret[j])
			j++;
		if (!(*str)[i])
			break ;
	}
	ret[j] = 0;
	return (ft_strdup_exit_and_free_src(&ret));
}

/*
** FT_APPLY_QUOTES_AND_ENV_VARS
** This function will take a string filled in with quotes and if there
** are parts inside between quotes, it will "apply" those quotes.
** Returns a malloc'd string copy without quotes, but with quotes applied
** Example: ft_apply_quotes("${PWD}") will return "/Users/ysoroko/Minishell"
**			ft_apply_quotes('${PWD}') will return "${PWD}"
*/

char	*ft_apply_quotes_and_env_vars(char **str)
{
	int		i;
	int		j;
	char	*ret;

	if (!str || !(*str))
		return (0);
	ft_initialize_variables(str, &i, &j, &ret);
	while ((*str)[++i])
	{
		ft_apply_conditions(str, &i, &j, &ret);
		if (ret[j])
			j++;
		if (!(*str)[i])
			break ;
	}
	ret[j] = 0;
	return (ft_strdup_exit_and_free_src(&ret));
}
