/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 13:54:29 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/20 14:35:32 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_extract_command_name(char *input, t_command *command)
{
	char	*temp;

	temp = ft_extract_first_word(input, SPACES);
	// "< test.txt cat" and "cat < test.txt" produce the same result
	if (!ft_strlcmp(temp, "<"))
	{
		command->redir_arg = ft_extract_second_word_qx(input, SPACES);


	}
}

void	ft_input_redirection(char *input, t_command *command)
{
	int	i;

	
}