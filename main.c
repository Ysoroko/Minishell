/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/03 14:05:48 by ysoroko          ###   ########.fr       */
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
	if (str)
		ft_free_str(str);
	if (lst)
		ft_dl_lstclear(lst, &ft_free_t_command);
}

/// Possible "errors":
// 1) CTRL + D sends an EOF to the STDIN, so the input becomes a NULL string
// 2) Only spaces in input
// 3) Unclosed quotes in input
int	ft_user_input_error(char *str)
{
	if (!str)
	{
		ft_putendl_fd("exit", STDOUT);
		exit(EXIT_SUCCESS);
	}
	if (!str[0])
		return (1);
	if (ft_str_has_unclosed_quotes(str))
	{
		ft_err(str, NULL, "Unclosed quotes error", 1);
		return (0);
	}
	return (0);
}

void	ft_prompt(char *path)
{
	char		*user_input_str;
	t_dl_lst	*input_as_dl_command_list;

	user_input_str = readline(PROMPT_NAME);
	if (ft_user_input_error(user_input_str))
	{
		free(user_input_str);
		return ;
	}
	add_history(user_input_str);
	if (ft_str_only_has_chars_from_charset(user_input_str, SPACES))
	{
		free(user_input_str);
		return ;
	}
	else if (ft_str_has_unclosed_quotes(user_input_str))
	{
		free(user_input_str);
		return ;
	}
	input_as_dl_command_list = ft_input_parsing(user_input_str, path);
	if (!ft_cmd_list_error(input_as_dl_command_list))
		ft_execute(input_as_dl_command_list);
	ft_cleanup_and_free(&user_input_str, input_as_dl_command_list);
}

int	main(int ac, char **av, char **env)
{
	char	origin[1024];
	char	*path;
	char	*builtins_path;

	if (!env)
		return (1);
	(void)ac;
	(void)av;
	builtins_path = NULL;
	g_glob.fork_ret = 0;
	ft_duplicate_env(env);
	getcwd(origin, 1024);
	ft_up_shlvl();
	path = ft_strjoin_exit(origin, "/builtins/");
	if (ft_env_index("EXIT_STATUS") != -1)
		ft_unset("EXIT_STATUS");
	ft_export("EXIT_STATUS=0");
	while (1)
	{
		g_glob.fork_ret = 0;
		ft_setup_signals();
		ft_prompt(path);
	}
	free(path);
	return (1);
}
