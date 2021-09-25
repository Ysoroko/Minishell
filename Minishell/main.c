/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/25 15:11:22 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
** FT_CLEANUP_AND_FREE
** This function is responsible for freeing everything that was malloc'd
** during a single user's input
** It frees the input saved as a string, and also the entire t_list and
** all of its content
*/

static void	ft_cleanup_and_free(char **str, t_dl_lst *lst)
{
	ft_free_str(str);
	ft_dl_lstclear(lst, &ft_free_t_command);
}

int	ft_user_input_error(char *str)
{
	char	*st;
	if (!str)
		kill(getpid(), SIGUSR1);
	if (ft_str_only_has_chars_from_charset(str, SPACES))
		return (1);
	if (ft_str_has_unclosed_quotes(str))
	{
		ft_putendl_fd("Minishell: Unclosed quotes error", STDERR);
		return (1);
	}
	return (0);
}

void	ft_prompt(void)
{
	char		*user_input_str;
	t_dl_lst	*input_as_dl_command_list;
	
	user_input_str = readline(PROMPT_NAME);
	if (ft_user_input_error(user_input_str))
		return ;
	add_history(user_input_str);
	if (ft_strcmp(user_input_str, "exit") == 0)
		exit(EXIT_SUCCESS);
	input_as_dl_command_list = ft_input_parsing(user_input_str);
	ft_execute(input_as_dl_command_list);
	ft_cleanup_and_free(&user_input_str, input_as_dl_command_list);
}

// cas d’erreur;
// ✅ -Input vide
// ✅ -Input composé uniquement de whitespaces
// ✅ -les 4 redirections si argument manquant
// ✅ -input avec que des pipes ou plusieurs pipes a la suite
// ✅ -2 ou + redirections a la suite
// ✅ -pipe sans commande a la suite
// ✅ "exi"
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	g_glob.env = env;
	while (1)
	{
		ft_setup_signals();
		ft_prompt();
	}
	return (1);
}
