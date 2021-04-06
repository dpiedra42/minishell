# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/06 14:48:03 by dpiedra           #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/04/06 18:35:02 by dpiedra          ###   ########.fr        #
=======
#    Updated: 2021/04/06 17:44:56 by dpiedra          ###   ########.fr        #
>>>>>>> 82c3ec7ad2767275e90ec1f5e3f2346c91b2e109
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft/libft.a

RM		= rm -rf

FLAGS	= -Wall -Wextra -Werror

CLANG	= clang

<<<<<<< HEAD
SRCS	= main.c parser/handle_basic.c parser/input_split.c parser/input_split2.c \
		  parser/parser_delegator.c parser/parser_error.c parser/parser_redir.c   \
		  parser/parser_redir2.c parser/parser_redir3.c parser/parser_variable.c  \
		  parser/parser.c parser/parser2.c builtins/cd_utils.c builtins/cd.c      \
		  builtins/echo.c builtins/env.c builtins/exec_utils.c builtins/exec.c 	  \
		  builtins/exit.c builtins/export_utils.c builtins/export.c builtins/pwd.c \
		  builtins/pipe.c builtins/signal.c builtins/unset.c

# SRCS	= main.c parser/parsing.c parser/parsing_utils.c builtins/ft_signal.c \
# 		  parser/parsing_split.c parser/parsing_special.c builtins/ft_echo.c  \
# 		  builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c \
# 		  builtins/ft_unset.c builtins/cd_utils.c parser/parsing_error.c \
# 		  parser/parsing_var.c parser/parsing_redir.c parser/parsing_exits.c \
# 		  builtins/ft_execute.c builtins/execute_utils.c builtins/ft_pipe.c \
# 		  parser/redir_utils.c builtins/ft_exit.c builtins/ft_export.c \
=======
SRCS	= main.c parser/parsing.c parser/parsing_utils.c builtins/ft_signal.c \
		  parser/parsing_split.c parser/parsing_filter.c parser/parsing_directory.c \
		  builtins/ft_echo.c builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c \
		  builtins/ft_unset.c builtins/cd_utils.c parser/parsing_error.c \
		  parser/parsing_var.c parser/parsing_redir.c builtins/export_utils.c \
		  builtins/ft_execute.c builtins/execute_utils.c builtins/ft_pipe.c \
		  parser/redir_utils.c builtins/ft_exit.c builtins/ft_export.c \
>>>>>>> 82c3ec7ad2767275e90ec1f5e3f2346c91b2e109

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
