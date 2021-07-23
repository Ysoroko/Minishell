/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:36:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/23 14:13:29 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

///*
//** FT_CHECK_FOR_PIPE
//** This functions checks if we have a redirection char in str_command
//** argument and stores it in t_command "pipe" element
//*/
//
//void	ft_check_for_pipe(char *str_command, t_command *command)
//{
//	int	len;
//
//	if (!str_command || !command)
//		return ;
//	len = ft_strlen(str_command);
//	if (ft_strchr(PIPES, str_command[len - 1]))
//		command->pipe = str_command[len - 1];
//}

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
	(*i)+= k - 1;
}

/*
** ft_add_word_after_redir_to_argument
** This function is used to add the words following the redirection argument
** to the command argument
** For example, "echo bonjour > test.txt au revoir" would
** create a "test,txt" file and write "bonjour au revoir" inside
** This function will append "au revoir" to "bonjour" extracted by a different
** funcion in t_command structure
*/

//void	ft_add_words_after_redir_to_argument(t_command *command, char *red_pos)
//{
//	int		i;
//	char	*temp;
//	char	*temp2;
//	char	len;
//
//	i = 0;
//	while (red_pos[i] && ft_strchr(SPACES, red_pos[i]))
//		i++;
//	temp = ft_pos_after_n_one_or_two_words(&(red_pos[i]), 2, SPACES);
//	if (!temp)
//		return ;
//	temp2 = ft_strdup_until_c_from_charset_not_quoted(temp, PIPES);
//	temp2 = ft_strtrim_exit_replace_src(&temp2, SPACES_AND_PIPES);
//	if (command->argument)
//		command->argument = ft_strjoin_free_pref_exit(&(command->argument), " ");
//	command->argument = ft_strjoin_free_pref_exit(&(command->argument), temp2);
//	ft_free_str(&temp2);
//}
