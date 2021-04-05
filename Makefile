# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/30 15:03:32 by dpiedra           #+#    #+#              #
#    Updated: 2021/04/05 17:00:29 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= main.c

SRCS	+= parser/parsing.c parser/parsing_split.c parser/parsing_special.c parser/parsing_var.c parser/parsing_redir.c

SRCS	+= parser/parsing_utils.c parser/parsing_error.c parser/parsing_exits.c parser/redir_utils.c

SRCS	+= builtins/ft_echo.c builtins/ft_pwd.c builtins/cd_utils.c builtins/ft_cd.c builtins/ft_execute.c builtins/execute_utils.c

SRCS	+= builtins/ft_env.c builtins/ft_export.c builtins/ft_unset.c builtins/ft_pipe.c builtins/ft_signal.c builtins/ft_exit.c

LIBFT	= libft/libft.a

OBJS	= $(SRCS:.c=.o)

NAME	= minishell

LIBFT	= libft/libft.a

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror

INCLUDE	= -L libft -lft




all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	cd libft && $(MAKE)
	$(CLANG) $(FLAGS) -o $(NAME) $(OBJS) $(INCLUDE)

clean:
	rm -f $(OBJS) $(B_OBJS)
	cd libft && $(MAKE) clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	cd libft && $(MAKE) fclean

re: fclean all

%.o: %.c
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)


# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-out.txt ./minishell
