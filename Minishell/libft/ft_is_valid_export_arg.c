/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_export_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 14:28:07 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/08 14:48:18 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/// Returns 1 if the string passed as argument is a valid.
/// Returns 0 and displays an error mesage otherwise.

int	ft_check_results(char *arg, char **before, char equal)
{
	char	*error_message;

	error_message = NULL;
	if (!equal)
		return (0); // $? = 0
	if (!*before) //or before not alphabet
	{
		error_message = ft_strjoin_exit("export: \'", arg);
		error_message = ft_strjoin_free_pref_exit(&error_message,
			"\': not a valid identifier");
	}
}

int	ft_is_valid_export_arg(char *arg)
{
	int		i;
	char	equal_char;
	char	*str_after_equal;
	char	*str_before_equal;
	char	*error_message;

	i = -1;
	equal_char = '\0';
	str_before_equal = 0;
	str_after_equal = 0;
	while (arg[++i])
	{
		if (!i && arg[i] != '=')
			str_before_equal = ft_strdup_until_c(arg, '=');
		if (arg[i] == '=' && i)
		{
			equal_char = '=';
			if (arg[i + 1])
				str_after_equal = ft_strdup_exit(&(arg[i + 1]));
		}
	}
	free(str_after_equal);
	free(str_before_equal);
	free(error_message);
	return (ft_check_results(arg, &str_before_equal, equal_char));
}
