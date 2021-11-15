# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 11:12:03 by ysoroko           #+#    #+#              #
#    Updated: 2021/11/15 17:48:36 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------ Sources ------------------------------

INPUT_PARSING		=	input_parsing/ft_user_input_to_dl_lst_with_commands.c \
						input_parsing/ft_extract_next_t_command.c \
						input_parsing/utils/ft_apply_quotes_and_env_vars.c \
						input_parsing/utils/ft_parsing_utils.c \
						input_parsing/utils/ft_quoted_copy.c \
						input_parsing/utils/ft_env_vars_utils.c \
						input_parsing/utils/ft_extract_str_tab_all.c \
						input_parsing/utils/ft_extract_str_tab_for_execve.c \
						input_parsing/utils/ft_extract_role_macros_tab.c \
						input_parsing/utils/ft_cmd_list_error.c \
						input_parsing/utils/ft_is_a_redirection_macro.c \
						input_parsing/utils/ft_role_macro_error.c \

EXECUTE				=	execute/ft_execute.c \
						execute/ft_check_if_cmd_exists.c \
						execute/ft_check_redir_and_binary.c \
						execute/ft_print_command_list.c \
						execute/ft_set_paths.c \
						execute/ft_hdoc.c \
						execute/ft_infile.c \
						execute/ft_outfile.c \
						execute/ft_env_utils.c \
						execute/ft_cmd.c \
						execute/ft_fdin.c \
						execute/ft_fdout.c \
						execute/ft_pipes.c \
						execute/ft_free_ressources.c \
						execute/ft_update_shlvl.c \
						execute/ft_hdoc_utils.c \

SIGNALS				=	signals/ft_signal_handler.c \
						signals/ft_hererdoc_signals.c \

BUILTINS			=	builtins/ft_export.c \
						builtins/ft_unset.c \
						builtins/ft_exit.c \
						builtins/ft_lstenv.c \
						builtins/ft_export_utils.c \
						builtins/ft_cd.c \

SRC					=	main.c $(INPUT_PARSING) $(EXECUTE) $(SIGNALS) $(BUILTINS)

OBJS				=	$(SRC:.c=.o)

LIBRARIES			=	libft/libft.a \
						minishell.a

# -------------------------------- Builtins exe sources  ---------------------------

BUILTINS_OBJS		=	$(BUILTINS:.c=.o)

ECHO_SRC			=	builtins/ft_echo.c \

ECHO_OBJ			=	$(ECHO_SRC:.c=.o)

ENV_SRC				=	builtins/ft_env.c \

ENV_OBJ				=	$(ENV_SRC:.c=.o)

PWD_SRC				=	builtins/ft_pwd.c \

PWD_OBJ				=	$(PWD_SRC:.c=.o)

BUILTINS_EXE		=	builtins/ft_echo \
						builtins/ft_env \
						builtins/ft_pwd

# ------------------------------ Flags / Commands ------------------------------

LINK				=	ar rcs

INCLUDE				=	-I include

EXECUTABLE			=	minishell

LIBFT				=	cd libft && make bonus

NAME				=	minishell.a

FLAGS				=	-Wall -Wextra -Werror -lreadline


# ------------------------------ Colors ------------------------------

BOLD_PURPLE			=	\033[1;35m

BOLD_CYAN			=	\033[1;36m

BOLD_YELLOW			=	\033[1;33m

NO_COLOR			=	\033[0m

BOLD_GREEN			=	\033[1;32m


# ------------------------------ Readline ------------------------------

RPATH		=	/Users/$(USER)/.brew/opt/readline/

READLINE_FLAGS	=	-L $(RPATH)lib -I $(RPATH)include -lreadline -Wno-unused-command-line-argument

RL_FLAGS	=	-L/usr/include  -lreadline

# This terminal setup line will get rid of "^C", "^D" etc. when pressing CTRL + C/D in minishell
REMOVE_CONTROL_CHARACTERS = stty -echoctl


# ------------------------------ Messages------------------------------

COMP_START	=	echo "\n🚧 $(BOLD_YELLOW)Make: $(NO_COLOR)Starting the compilation...\n"

COMPILING_LIBFT	=	@echo "\n📚 $(BOLD_GREEN)Compiling Libft... \n";

MINISHELL_COMPILED = echo "\n🐚 $(BOLD_PURPLE)Executable $(BOLD_CYAN)\"$(EXECUTABLE)\" $(BOLD_PURPLE)created and ready for use!\n$(NO_COLOR)"

CLEANED		=	echo "\n🧼 $(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n🧽 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed all the \".a\" files and the executables \n"						


# ------------------------------ Rules ------------------------------

all: $(NAME)

$(NAME): $(OBJS) $(ECHO_OBJ) $(PWD_OBJ) $(ENV_OBJ)
		@make comp_start
		@make mini
		@make ft_echo
		@make ft_env ft_pwd
		@$(REMOVE_CONTROL_CHARACTERS)
		@$(MINISHELL_COMPILED)

# Compiles everything with warning flags and runs the executable
run:	$(NAME)
		@./$(EXECUTABLE)

# Remove all ".o" files
clean:
		@cd libft && make clean
		@rm -rf $(OBJS)
		@rm -rf $(BUILTINS_OBJS)
		@rm -rf $(ECHO_OBJ)
		@rm -rf $(PWD_OBJ)
		@rm -rf $(ENV_OBJ)
		@$(CLEANED)

# Remove all ".o / .a / minishell executable" files
fclean:	clean
		@rm -rf $(NAME)
		@rm -rf $(EXECUTABLE)
		@cd libft && make fclean
		@rm -rf $(BUILTINS_EXE)
		@$(FCLEANED)

re:		fclean all

comp_start:
	@$(COMP_START)
	@$(COMPILING_LIBFT)
	@$(LIBFT)

mini: $(OBJS)
	@$(LINK) $(NAME) $(OBJS)
	@gcc $(FLAGS) $(READLINE_FLAGS) $(RL_FLAGS) $(LIBRARIES) -o $(EXECUTABLE)

ft_echo: $(ECHO_OBJ)
	@gcc $(FLAGS) $(READLINE_FLAGS) $(RL_FLAGS) $(ECHO_OBJ) libft/libft.a minishell.a -o ft_echo ; mv ft_echo builtins/

ft_env: $(ENV_OBJ)
	@gcc $(FLAGS) $(ENV_SRC) libft/libft.a minishell.a -o ft_env ; mv ft_env builtins/

ft_pwd: $(PWD_OBJ)
	@gcc $(FLAGS) $(READLINE_FLAGS) $(RL_FLAGS) $(PWD_OBJ) libft/libft.a minishell.a -o ft_pwd ; mv ft_pwd builtins/

.c.o:
	@gcc $(FLAGS) $(READLINE_FLAGS) $(RL_FLAGS) -I include -c $< -o ${<:.c=.o}

.PHONY: all clean fclean re run wrun .c.o
