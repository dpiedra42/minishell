# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 14:48:03 by dpiedra           #+#    #+#              #
#    Updated: 2021/04/12 17:25:41 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft/libft.a

RM		= rm -rf

FLAGS	= -Wall -Wextra -Werror

CLANG	= clang

SRCS	= main.c parser/parsing.c parser/parsing_utils.c builtins/ft_signal.c \
		  parser/parsing_split.c parser/parsing_filter.c builtins/ft_echo.c  \
		  builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c builtins/export_utils.c \
		  builtins/ft_unset.c builtins/cd_utils.c parser/parsing_error.c \
		  parser/parsing_var.c parser/parsing_redir.c parser/parsing_directory.c \
		  builtins/ft_execute.c builtins/execute_utils.c builtins/ft_pipe.c \
		  parser/redir_utils.c builtins/ft_exit.c builtins/ft_export.c \
		  termcaps/ft_history.c

OBJS	= $(SRCS:.c=.o)


all:	$(NAME)

.PHONY:	clean fclean re

$(NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS) -L libft -lft

clean:
	$(RM) $(OBJS)
	cd libft && $(MAKE) clean

fclean: clean
	$(RM) $(NAME)
	cd libft && $(MAKE) fclean

re: fclean all

%.o: %.c
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)
	
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./minishell
