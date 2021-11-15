/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:07:01 by ysoroko           #+#    #+#             */
/*   Updated: 2021/11/15 17:51:37 by ysoroko          ###   ########.fr       */
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
# include <dirent.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_glob
{
	pid_t	fork_ret;
	char	**env;
}	t_glob;

/*
** LA VARIABLE GLOBALE
*/

t_glob		g_glob;

/*
** MINISHELL PROMPT DISPLAY CONSTANTS
*/

# define PROMPT_NAME "minishell: "
# define PROMPT_COLOR "\033[1m\033[36m"
# define PROMPT_ERROR "minishell: "

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
# define EXIT_STATUS "EXIT_STATUS"

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
	int		error;
	int		exists;
	int		fdin;
	int		fdout;
	int		redir_type_in;
	int		redir_type_out;
	char	*infile;
	char	*outfile;
	char	**keyword;
	int		keyword_index;
	char	*buffer;
	int		s;
	char	*path;
}	t_command;

/*
** PROTOTYPES
*/

t_dl_lst	*ft_input_parsing(char *input, char *path);
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
void		ft_extract_role_macros_tab(t_command *command);
void		ft_print_command_list(void *current_command);
int			ft_is_a_redir_arg_macro(int macro);
void		ft_prompt(char *path);
void		ft_setup_signals(void);
int			ft_check_file_permissions(char *filename);
int			ft_open_hdoc(t_command *cmd, int *fd);
void		ft_close_hdoc(t_command *cmd, int *fd);
void		ft_hdoc(t_command *cmd);
void		ft_copy_outfile(t_command *cmd, int i);
void		ft_add_redir_out(t_command *cmd, int m, int i);
void		ft_copy_infile(t_command *cmd, int i);
void		ft_add_redir_in(t_command *cmd, int i);
void		ft_add_redir_hdoc(t_command *cmd, int i);
void		ft_add_redir_files(t_command *cmd, int m, int i);
int			ft_exec_check(char *path, char *cmd);
char		**ft_split_paths(int *i);
void		ft_join_paths(char **paths, int i);
int			ft_set_paths(char **exec_name);
int			ft_check_binary(char *filename);
void		ft_check_tables(t_command *command);
void		ft_check_if_cmd_exists(t_command *command);
void		ft_check_redir_and_binary(void *current_command);
int			ft_builtin_cmd_found(char *exec_name);
int			ft_nb_env(char **env);
int			ft_cmp_env(char *s1, char *s2);
int			ft_env_index(char *s);
void		ft_duplicate_env(char **env);
void		ft_exit(int n);
void		ft_unset(char *var);
int			ft_export(char *new_var);
void		ft_close_pipes(int npipes, int *pfd);
void		ft_open_pipes(int npipes, int *pfd);
void		ft_fdin(t_command *cmd);
void		ft_fdout(t_command *cmd);
void		ft_pipe_cmd(t_dl_lst *command_list, t_command *cmd, int *pfd,
				int j);
void		ft_setup_for_exec(t_dl_lst *lst, int **pfd, int *npipes, int *j);
void		ft_fds_and_pipes(t_dl_lst *lst, t_command *cmd, int *pfd, int j);
void		ft_parent_process(int npipes, int *pfd);
int			ft_builtin_cmd_found(char *exec_name);
char		*ft_getenv(char *s);
void		ft_export_handler(t_command *cmd);
void		ft_unset_handler(t_command *cmd);
int			ft_cmd_handler(t_command *cmd);
void		ft_cmd_handler_no_fork(t_command *cmd, int s);
void		ft_execute(t_dl_lst *command_list);
int			ft_check(char *s);
int			ft_is_valid_export_arg(char *arg);
void		ft_free_ressources(t_command *cmd);
void		ft_up_shlvl(void);
void		ft_down_shlvl(void);
void		ft_exit_cmd(t_command *cmd);
t_list		*ft_tab_to_list(void);
void		ft_clear_node(void *content);
char		**ft_list_to_tab(t_list *lst);
void		ft_delete(t_list **lst, char *var);
char		*ft_until(char *src, char c);
void		ft_cd(t_command *cmd);
void		ft_display_signal_message(int status_code);
int			ft_cmd_list_error(t_dl_lst *lst);
void		ft_heredoc_signals_setup(void);
void		ft_wait_and_update_exit_status_hdoc(void);
int			ft_is_a_redirection_macro(int m);
void		ft_open_hdoc_file(t_command *cmd, int *fd);
int			ft_role_macro_error(char *current_element);
int			ft_error_macro_present(int *macros, int len);
char		*ft_apply_env_vars(char **str);

/*
** COLORS
*/

# define COLOR_RESET "\x1b[0m"

# define BOLDRED "\033[1m\033[31m"
# define BOLDGREEN "\033[1m\033[32m"
# define BOLDYELLOW "\033[1m\033[33m"
# define BOLDBLUE "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN "\033[1m\033[36m"
# define BOLDWHITE "\033[1m\033[37m"

#endif