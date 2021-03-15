# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/30 15:03:32 by dpiedra           #+#    #+#              #
#    Updated: 2021/03/15 17:41:35 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RM		= rm -rf

FLAGS	= -Wall -Wextra -Werror

CLANG	= clang

SRCS	= main.c parsing.c parsing_utils.c ft_signal.c parsing_split.c \
		  parsing_special.c ft_echo.c ft_pwd.c ft_env.c ft_cd.c cd_utils.c  \
		  parsing_escape.c parsing_var.c parsing_quotes.c parsing_exits.c   \
		  ft_execute.c execute_utils.c

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