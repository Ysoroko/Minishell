/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_export_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:28:07 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/02 17:21:41 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_not_alpha_str(char *str)
{
	int	i;

	i = -1;
	while (++i)
	{
		if (!ft_isalpha(str[i]))
			return (1);
	}
	return (0);
}

static int	ft_free_all(char *error, char *before, char *after, int ret)
{
	free(error);
	free(before);
	free(after);
	return (ret);
}

/// Returns 1 if the string passed as argument is a valid.
/// Returns 0 and displays an error mesage otherwise.
/// If (!equal) -> $? = 0
/// if only redirs after = -> $? = 258

int	ft_check_results(char *arg, char **before, char **after, char equal)
{
	char	*error_message;

	error_message = NULL;
	if (!(*before) || !ft_isalpha((arg)[0]))
	{
		error_message = ft_strjoin_exit("export: \'", arg);
		error_message = ft_strjoin_free_pref_exit(&error_message,
				"\': not a valid identifier");
		ft_modify_exit_status(1);
		ft_minishell_error(error_message);
		return (ft_free_all(error_message, *before, *after, 0));
	}
	if (!equal)
		return (ft_free_all(error_message, *before, *after, 1));
	if (*after && ft_str_only_has_chars_from_charset(*after, REDIRS))
	{
		ft_minishell_error("syntax error");
		ft_modify_exit_status(258);
		return (ft_free_all(error_message, *before, *after, 0));
	}
	return (ft_free_all(error_message, *before, *after, 1));
}

/// Returns 0 if the argument is invalid
/// Returns 1 if the argument is ok
/// Example of invalid arguments:
/// 1) "export test" (test -> no '=' char, this does nothing)
/// 2) "export 1456=ok" (1456 -> starts by a non letter) (A456 OK)
/// 3) "export =test" (=test ->no variable name before '=')
int	ft_is_valid_export_arg(char *arg)
{
	int		i;
	char	equal;
	char	*str_after_equal;
	char	*str_before_equal;

	i = -1;
	equal = '\0';
	str_before_equal = 0;
	str_after_equal = 0;
	while (arg[++i])
	{
		if (!i && arg[i] != '=')
			str_before_equal = ft_strdup_until_c(arg, '=');
		if (arg[i] == '=' && i)
		{
			equal = '=';
			if (arg[i + 1])
			{
				str_after_equal = ft_strdup_exit(&(arg[i + 1]));
				break ;
			}
		}
	}
	return (ft_check_results(arg, &str_before_equal, &str_after_equal, equal));
}
