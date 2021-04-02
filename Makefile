# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/30 15:03:32 by dpiedra           #+#    #+#              #
#    Updated: 2021/04/02 17:45:50 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft/libft.a

RM		= rm -rf

FLAGS	= -Wall -Wextra -Werror

CLANG	= clang

SRCS	= main.c parser/parsing.c parser/parsing_utils.c builtins/ft_signal.c \
		  parser/parsing_split.c parser/parsing_special.c builtins/ft_echo.c  \
		  builtins/ft_pwd.c builtins/ft_env.c builtins/ft_cd.c \
		  builtins/ft_unset.c builtins/cd_utils.c parser/parsing_error.c \
		  parser/parsing_var.c parser/parsing_redir.c parser/parsing_exits.c \
		  builtins/ft_execute.c builtins/execute_utils.c builtins/ft_pipe.c \
		  parser/redir_utils.c builtins/ft_exit.c builtins/ft_export.c \

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