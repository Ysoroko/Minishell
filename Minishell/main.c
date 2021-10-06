/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:52:17 by ysoroko           #+#    #+#             */
/*   Updated: 2021/10/06 15:18:01 by ablondel         ###   ########.fr       */
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

int	ft_nb_env(char **env)
{
	int i = 0;

	while (env[i])
		i++;
	return (i);
}

int	ft_cmp_env(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*(s1 + 1) && *(s1 + 1) == '=')
			return (0);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_env_index(char *s)
{
	int i = 0;
	int j = ft_nb_env(g_glob.env);

	while (g_glob.env[i] && i < j)
	{
		if (ft_cmp_env(g_glob.env[i], s) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	ft_duplicate_env(char **env)
{
	int i = 0;

	g_glob.env = (char**)malloc(sizeof(char*) * (ft_nb_env(env) + 1));
	if (!g_glob.env)
	{
		printf("%s\n", strerror(ENOMEM));
		exit(EXIT_FAILURE);
	}
	while (i < ft_nb_env(env))
	{
		g_glob.env[i] = ft_strdup_exit(env[i]);
			i++;
	}
	g_glob.env[i] = NULL;
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	ft_duplicate_env(env);
	g_glob.main_pid = getpid();
	while (1)
	{
		g_glob.fork_ret = g_glob.main_pid;
		ft_setup_signals();
		ft_prompt();
	}
	return (1);
}
