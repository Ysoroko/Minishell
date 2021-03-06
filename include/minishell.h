/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:07:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/07/27 11:03:46 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termcap.h>
# include <termios.h>
# include "libft.h"
# include <string.h>
# include <sys/errno.h>


/*
** MINISHELL PROMPT DISPLAY CONSTANTS
*/

# define PROMPT_NAME "minishell: "
# define PROMPT_COLOR "\033[1m\033[36m"

/*
** CONSTANT PARAMETERS
*/

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define INPUT_SIZE 1000
# define MAX_INPUT_SIZE 262144
# define SPACES " \t\n\r\v\f"
# define REDIRS "><"
# define PIPES "|"
# define SPACES_REDIRS_PIPES " \t\n\r\v\f><|"
# define REDIRS_AND_PIPES "><|"
# define SPACES_AND_PIPES " \t\n\r\v\f|"
# define REDIRS_PIPES_QUOTES "><|\'\""
# define SPACES_AND_REDIRECTIONS " \t\n\r\v\f><"
# define BACKSLASH_IN_DQ_CHARS "$`\"\n"
# define ENV_VAR_SEPS " \t\n\r\v\f><|"
# define COMMAND_NAMES "echo cd pwd export unset env exit"
# define LINE_LENGTH 70
# define PLACE_FOR_I -2

/*
** INT_TAB_MACROS
*/

# define ERROR 0
# define REDIR_R 1
# define REDIR_RR 2
# define REDIR_L 3
# define REDIR_LL 4
# define REDIR_ARG 5
# define PIPE 6
# define COMMAND 7
# define FLAG 8
# define COMMAND_ARG 9
# define R_REDIR_ARG 10
# define L_REDIR_ARG 11
# define RR_REDIR_ARG 12
# define LL_REDIR_ARG 13

/*
** STRUCTURES
** To use it with "execve": array of strings with []
*/

typedef struct s_command
{
	char	**str_tab_all;
	char	**str_tab_for_execve;
	int		*role_macros;
}	t_command;

/*
** PROTOTYPES
*/

t_dl_lst	*ft_input_parsing(char *input);
void		ft_free_t_command(void *command_pointer);
void		ft_update_str_read_so_far(char *input_checkpt, int i, char **prev);
t_command	*ft_extract_next_t_command(char *input_checkpnt, int *i);
void		ft_execute(t_dl_lst *command_list);
void		ft_signal_handler(int no_matter);
void		ft_initialize_termcaps(char **term_type, int *ret);
char		*ft_extract_next_command_string(char *input_checkpoint);
void		ft_check_for_unclosed_quotes(char **input);
void		ft_check_for_pipe(char *str_command, t_command *command);
char		*ft_apply_quotes_and_env_vars(char **str);
void		ft_append_env_var_value(char *str, char **dest, int *i, int *j);
int			ft_calculate_total_length_needed(char *str);
void		ft_quoted_copy(char *str, char **dest, int *i, int *j);
char		ft_env_var_delimiter(char *str_start_with_dollar_sign);
void		ft_add_words_after_redir_to_argument(t_command *command,
				char *red_pos);
void		ft_copy_spaces(char *src, char **dest, int *i, int *j);
void		ft_display_prompt(char *color, char *prompt_name);
void		ft_extract_str_tab_all(char *next_command_str, t_command *command);
void		ft_extract_str_tab_for_execve(t_command *command);
int			ft_str_is_a_redirection(char *str);
void 		ft_extract_role_macros_tab(t_command *command);
void		ft_print_command_list(void *current_command);
int			ft_is_a_redir_arg_macro(int macro);

/*
** COLORS
*/

# define COLOR_RESET   "\x1b[0m"

# define BOLDRED "\033[1m\033[31m"
# define BOLDGREEN "\033[1m\033[32m"
# define BOLDYELLOW "\033[1m\033[33m"
# define BOLDBLUE "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN "\033[1m\033[36m"
# define BOLDWHITE "\033[1m\033[37m"

#endif