# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/30 15:03:32 by dpiedra           #+#    #+#              #
#    Updated: 2021/03/10 13:59:11 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RM		= rm -rf

FLAGS	= -Wall -Wextra -Werror

CLANG	= clang

SRCS	= main.c parsing.c parsing_utils.c signal_handler.c parsing_split.c \
		  parsing_special.c ft_echo.c ft_pwd.c ft_env.c ft_cd.c cd_utils.c  \
		  parsing_escape.c parsing_var.c parsing_quotes.c

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