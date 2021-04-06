# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpiedra <dpiedra@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/07 14:03:22 by dpiedra           #+#    #+#              #
#    Updated: 2021/04/06 15:39:08 by dpiedra          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

RM		=	rm -f

CFLAGS	= 	-Wall -Wextra -Werror

CC		=	gcc

HEADER	=	libft.h

SRCS	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
		 	ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c \
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_substr.c ft_strjoin.c  ft_strtrim.c ft_split.c \
			ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_itoa_base.c get_next_line.c \
			ft_strcmp.c ft_strstr.c ft_putchar.c ft_putstr.c

SBONUS	=	ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
			ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
			ft_lstmap_bonus.c

OBJ		=	$(SRCS:.c=.o)

OBONUS	=	$(SBONUS:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
			$(CC) $((SRCS) libft.h $(CFLAGS) 
			ar -rcs $(NAME) $(OBJ) $(HEADER)

bonus	:	$(OBONUS)
			$(CC) $((SBONUS) libft.h $(CFLAGS) 
			ar -rcs $(NAME) $(OBONUS) $(HEADER)	

clean	:
			$(RM) $(OBJ) $(OBONUS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all
