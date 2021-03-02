# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/30 15:03:32 by dpiedra           #+#    #+#              #
#    Updated: 2021/03/02 17:42:47 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

RM		= rm -rf

FLAGS	= -Wall -Wextra -Werror

CLANG	= clang

SRCS	= main.c parsing.c parsing_utils.c signal_handler.c parsing_split.c \
		  parsing_special.c ft_echo.c ft_pwd.c ft_env.c

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