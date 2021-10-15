# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/25 11:12:03 by ysoroko           #+#    #+#              #
#    Updated: 2021/10/15 11:16:42 by ablondel         ###   ########.fr        #
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
						execute/ft_update_dir.c \

BUILTINS			=	builtins/ft_export.c \
						builtins/ft_unset.c \
						builtins/ft_exit.c \

BUILTINS_EXE		=	builtins/ft_echo \

SIGNALS				=	signals/ft_signal_handler.c

SRC					=	main.c $(INPUT_PARSING) $(EXECUTE) $(SIGNALS) $(BUILTINS)

LIBRARIES			=	libft/libft.a \
						minishell.a

OBJS				=	$(SRC:.c=.o)

# ------------------------------ Flags / Commands ------------------------------

LINK				=	ar rcs

INCLUDE				=	-I include

EXECUTABLE			=	minishell

LIBFT				=	cd libft && make bonus

NAME				=	minishell.a

FLAGS				=	-Wall -Wextra -Werror -lreadline -fsanitize=address


# ------------------------------ Colors ------------------------------

BOLD_PURPLE			=	\033[1;35m

BOLD_CYAN			=	\033[1;36m

BOLD_YELLOW			=	\033[1;33m

NO_COLOR			=	\033[0m


# ------------------------------ Readline ------------------------------

USER		=	ysoroko

RPATH		=	/Users/$(USER)/.brew/opt/readline/

READLINE_FLAGS	=	-L $(RPATH)lib -I $(RPATH)include -lreadline -Wno-unused-command-line-argument

RL_FLAGS	=	-L/usr/include  -lreadline

# This terminal setup line will get rid of "^C", "^D" etc. when pressing CTRL + C/D in minishell
REMOVE_CONTROL_CHARACTERS = stty -echoctl


# ------------------------------ Messages------------------------------

MINISHELL_COMPILED = echo "\n🐚 $(BOLD_PURPLE)Executable $(BOLD_CYAN)\"$(EXECUTABLE)\" $(BOLD_PURPLE)created and ready for use!\n$(NO_COLOR)"

CLEANED		=	echo "\n🧼 $(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files \n"

FCLEANED	=	echo "\n🧽 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed all the \".a\" files and the \"minishell\" executable \n"						


# ------------------------------ Rules ------------------------------

.c.o:
	@${CC} ${CFLAGS} $(READLINE_FLAGS) $(RL_FLAGS) -I include -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
		@$(LIBFT)
		@$(LINK) $(NAME) $(OBJS)
		@gcc $(FLAGS) $(READLINE_FLAGS) $(RL_FLAGS) builtins/ft_echo.c libft/libft.a minishell.a -o ft_echo ; mv ft_echo builtins/
		@gcc $(FLAGS) $(READLINE_FLAGS) $(RL_FLAGS) $(LIBRARIES) -o $(EXECUTABLE)
		@$(REMOVE_CONTROL_CHARACTERS)
		@$(MINISHELL_COMPILED)


# Compiles everything with warning flags and runs the executable
run:	$(NAME)
		@$(REMOVE_CONTROL_CHARACTERS)
		@./$(EXECUTABLE)

# Compiles everything without warning flags and runs the executable
wrun:	$(NAME)
		@gcc $(LIBRARIES) $(TERMCAP) -o $(EXECUTABLE) && ./$(EXECUTABLE)

# Remove all ".o" files
clean:
		@rm -rf $(OBJS)
		@cd libft && make clean
		@$(CLEANED)

# Remove all ".o / .a / minishell executable" files
fclean:	clean
		@rm -rf $(NAME)
		@rm -rf $(EXECUTABLE)
		@cd libft && make fclean
		@rm -rf $(BUILTINS_EXE)
		@$(FCLEANED)

re:		fclean all

.PHONY: all clean fclean re run wrun .c.o