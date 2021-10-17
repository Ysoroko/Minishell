/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_export_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:28:07 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/17 15:17:02 by ysoroko          ###   ########.fr       */
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

/// Returns 1 if the string passed as argument is a valid.
/// Returns 0 and displays an error mesage otherwise.
/// If (!equal) -> $? = 0
/// if only redirs after = -> $? = 258

int	ft_check_results(char *arg, char **before, char **after, char equal)
{
	char	*error_message;

	error_message = NULL;
	g_glob.exit_status = 0;
	if (!equal)
		return (0);
	if (!*before || ft_not_alpha_str(*before) || !ft_strlcmp(*before, "?"))
	{
		error_message = ft_strjoin_exit("export: \'", arg);
		error_message = ft_strjoin_free_pref_exit(&error_message,
				"\': not a valid identifier");
		g_glob.exit_status = 1;
		ft_minishell_error(error_message);
	}
	if (*after && !ft_str_only_has_chars_from_charset(*after, REDIRS))
	{
		ft_minishell_error("syntax error");
		g_glob.exit_status = 258;
	}
	free(error_message);
	free(*before);
	free(*after);
	return (1);
}

/// Returns 0 if the argument is invalid
/// Returns 1 if the argument is ok
/// Example of invalid arguments:
/// 1) "export test" (test -> no '=' char, this does nothing)
/// 2) "export 1456=ok" (1456 -> not alphabet characters in name)
/// 3) "export =test" (=test ->no variable name before '=')
/// 4) "export ?=48" : bash: export: `?=48': not a valid identifier
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
				str_after_equal = ft_strdup_exit(&(arg[i + 1]));
		}
	}
	return (ft_check_results(arg, &str_before_equal, &str_after_equal, equal));
}
