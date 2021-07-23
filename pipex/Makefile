CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_check_permissions.c \
ft_free_tab.c \
ft_len.c \
ft_memzero.c \
ft_nb_options.c \
ft_nb_paths.c \
ft_print_error.c \
ft_set_all_paths.c \
ft_split_args.c \
ft_split.c \
ft_strcmp.c \
ft_strdup.c \
ft_strjoin.c \
ft_setup_args.c \
ft_process_handling.c \
pipex.c

OBJ = ${SRC:.c=.o}

NAME = pipex

$(NAME):		$(OBJ)
			$(CC)	-o $(NAME) 	$(OBJ)

all:		$(NAME)

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY: all clean fclean re
