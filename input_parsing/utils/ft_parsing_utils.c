/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/03 10:25:28 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** FT_FREE_T_COMMAND
** This function is used to free the t_command structure's elements,
** set al of them to NULL pointers using ft_free_str to avoid double free
** and then free and set t_command to NULL itself
*/

void	ft_free_t_command(void *command_pointer)
{
	t_command	*command;

	if (!command_pointer)
		return ;
	command = (t_command *)(command_pointer);
	if (command->str_tab_all)
		ft_free_str_tab(&(command->str_tab_all), 0);
	if (command->str_tab_for_execve)
		ft_free_str_tab(&(command->str_tab_for_execve), 0);
	if (command->role_macros)
		ft_free_int_tab(&(command->role_macros), 0);
	free(command_pointer);
	command_pointer = 0;
}

/*
** FT_EXTRACT_NEXT_COMMAND_STRING
** This function will create a malloc'd duplicate of inupt_checkpoint
** argument, ending at the first redirection character
*/

char	*ft_extract_next_command_string(char *checkpoint)
{
	char	*ret;

	ret = ft_strdup_until_c_from_charset_not_quoted(checkpoint, PIPES);
	if (ft_str_only_has_chars_from_charset(ret, SPACES))
		ft_free_str(&ret);
	return (ret);
}

/*
** int	ft_str_is_a_redirection(char *str)
** This function returns the corresponding redirection macro
** if str argument is a redirection string (one of: ">" ">>" "<" "<<")
** If it's not a redirection, it will return 0.
*/

int	ft_str_is_a_redirection(char *str)
{
	if (!ft_strlcmp(str, ">"))
		return (REDIR_R);
	else if (!ft_strlcmp(str, ">>"))
		return (REDIR_RR);
	else if (!ft_strlcmp(str, "<"))
		return (REDIR_L);
	else if (!ft_strlcmp(str, "<<"))
		return (REDIR_LL);
	else
		return (0);
}

/*
** ft_copy_spaces
** This function is used when we encounter spaces in *src
** It will skip all the spaces in src and copy only one space in *dest
*/

void	ft_copy_spaces(char *src, char **dest, int *i, int *j)
{
	int	k;

	k = 0;
	while (src[k] && ft_isspace(src[k]))
		k++;
	((*dest)[*j] = ' ');
	(*i) += k - 1;
}

int	ft_is_a_redir_arg_macro(int macro)
{
	if (macro == REDIR_ARG)
		return (REDIR_ARG);
	if (macro == R_REDIR_ARG)
		return (R_REDIR_ARG);
	if (macro == L_REDIR_ARG)
		return (L_REDIR_ARG);
	if (macro == RR_REDIR_ARG)
		return (RR_REDIR_ARG);
	if (macro == LL_REDIR_ARG)
		return (LL_REDIR_ARG);
	return (0);
}
