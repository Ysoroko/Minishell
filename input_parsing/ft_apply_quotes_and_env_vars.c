/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_quotes_and_env_vars.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:43:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/19 14:55:00 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	char	*my_str;
	char	*ret;

	if (!str || !(*str))
		return (0);
	my_str = *str;
	printf(BOLDRED);
	//printf("\nmy_str = [%s]\n\n", my_str);
	printf(COLOR_RESET);
	i = -1;
	j = 0;
	ret = ft_calloc_exit(ft_calculate_total_length_needed(*str), 1);
	while (my_str[++i])
	{
		printf(BOLDGREEN);
		//printf("\n&(my_str[i]) = [%s]\n\n", &(my_str[i]));
		printf(COLOR_RESET);
		if (ft_isspace(my_str[i]))
			ft_copy_spaces(&(my_str[i]), &ret, &i, &j);
		else if (my_str[i] == '$' && ft_is_env_name_char(my_str[i + 1]))
		{
			printf(BOLDMAGENTA);
			//printf("appending env_var value at &str[i]: [%s]\n", &(my_str[i]));
			printf(COLOR_RESET);
			ft_append_env_var_value(&(my_str[i]), &ret, &i, &j);
		}
		else if (my_str[i] == '$' && (my_str[i + 1] == '\'' || my_str[i + 1] == '\"'))
			;
		else if (ft_char_is_a_start_quote(my_str, i))
		{
			printf(BOLDYELLOW);
			//printf("going to quoted_copy at &str[i]: [%s]\n", &(my_str[i]));
			printf(COLOR_RESET);
			ft_quoted_copy(&(my_str[i]), &ret, &i, &j);
		}
		else
		{
			printf(BOLDBLUE);
			//printf("copying my_str[i]: [%c] to ret[j]\n", my_str[i]);
			printf(COLOR_RESET);
			ret[j] = my_str[i];
		}
		if (ret[j])
			j++;
		if (!my_str[i])
			break;
	}
	ret[j] = 0;
	return (ft_strdup_exit_and_free_src(&ret));
}
