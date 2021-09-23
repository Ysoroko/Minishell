/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/09/23 15:48:54 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

/*
** FT_DISPLAY_PROMPT
** This function is used to display the prompt name on STDOUT in the specified
** color
** The last line is used to reset the color after displaying the prompt
** so that the input is written in standard white
*/

void	ft_display_prompt(char *color, char *prompt_name)
{
	write(STDOUT, color, 10);
	write(STDOUT, prompt_name, (int)ft_strlen(prompt_name));
	write(STDOUT, "\x1b[0m", 5);
}

/*
** FT_EXTRACT_USER_INPUT_TO_STRING
** This function will transform user's input input into one string
** It will also check for unclosed quotes in the input
*/

static void	ft_extract_user_input_to_string(char **str)
{
	char	*temp;
	char	unclosed_quote;
	int		read_ret;
	
	*str = ft_calloc_exit(sizeof(char), INPUT_SIZE);
	read_ret = ft_read_exit(STDIN, *str, INPUT_SIZE);
	if (!read_ret)
		ft_signal_handler(SIGUSR1);
	if (!ft_strchr(*str, '\n'))
		printf("\nEOF Seen\n");
	if (!read_ret && *str && !ft_str_only_has_chars_from_charset(*str, SPACES))
		ft_signal_handler(SIGUSR1);
	else if (read_ret && *str && !ft_str_only_has_chars_from_charset(*str, SPACES))
		ft_check_for_unclosed_quotes(str);
	else
		ft_free_str(str);
}

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

/*
** FT_CHECK_FOR_UNCLOSED_QUOTES
** This function is used to analyze user's input
** and if it has unclosed quotes, it will display ">"
** in prompt until the unclosed quote is provided in input
*/

void	ft_check_for_unclosed_quotes(char **input)
{
	char	*additional_input;

	if (!input || !*input)
		return ;
	if (ft_str_has_unclosed_quotes(*input))
	{
		additional_input = ft_calloc_exit(sizeof(char), INPUT_SIZE);
		while (ft_str_has_unclosed_quotes(*input))
		{
			ft_display_prompt(BOLDCYAN, "> ");
			ft_read_exit(STDIN, additional_input, INPUT_SIZE);
			*input = ft_strjoin_free_pref_exit(input, additional_input);
		}
		ft_free_str(&additional_input);
	}
	*input = ft_strtrim_exit_replace_src(input, SPACES);
}

/*
** FT_SETUP_SIGNALS
** This function modifies the behaviour when specific actions are done
** When we press CTRL+C, instead of quitting it will call the function
** ft_signal handlerz
*/

static void	ft_setup_signals(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	signal(SIGUSR1, ft_signal_handler);
}

/*
** MAIN
** Central hub of the minishell project
** Here we display the "minishell" prompt and extract user's input.
** The parsing then transforms user's input from a string format to a double
** linked list format (a linked list where each element has the address of both
** the next and the previous element of the list)
** It executes all of the commands from the user's input one by one
** Cleans up and frees all used data after each user's input
*/

void	print(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("[%s]\n", tab[i]);
		i++;
	}
	printf("\n\n");
}

int	ft_check_spaces(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

int	ft_empty_input(char *input)
{
	if (!input)
		return (0);
	while (*input)
	{
		if (!ft_check_spaces(*input, SPACES))
			return (1);
		input++;
	}
	return (-1);
}

void	ft_prompt()
{
	char		*user_input_str;
	t_dl_lst	*input_as_dl_command_list;
	
	user_input_str = readline("minishell: ");
	if (!user_input_str || !user_input_str[0])
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

	ft_setup_signals();
	g_env = env;
	while (1)
	{
		ft_prompt();
	}
	return (1);
}
