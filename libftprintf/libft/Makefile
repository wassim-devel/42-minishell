# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoizel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 09:39:47 by aoizel            #+#    #+#              #
#    Updated: 2024/01/09 13:14:21 by bli              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
INCLUDES = libft.h
CC = cc $(CFLAGS)
SOURCES = 	ft_toupper.c ft_bzero.c ft_strmapi.c ft_putchar_fd.c \
			ft_putstr_fd.c ft_strjoin.c ft_memmove.c ft_split.c \
			ft_strtrim.c ft_strnstr.c ft_memcmp.c ft_tolower.c \
			ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
			ft_strcmp.c ft_putendl_fd.c ft_isascii.c ft_isalnum.c \
			ft_itoa.c ft_atoi.c ft_memcpy.c ft_memset.c ft_putnbr_fd.c \
			ft_strrchr.c ft_isalpha.c ft_isdigit.c ft_isprint.c \
			ft_substr.c ft_memchr.c ft_strdup.c ft_strchr.c \
			ft_striteri.c ft_calloc.c \
			ft_lstnew.c ft_lstadd_front.c \
			ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean fclean re bonus

all : $(NAME) 

$(NAME) : $(OBJECTS) 
	ar -rc $@ $^

%.o : %.c $(INCLUDES)
	$(CC) -c -I. $<

clean : 
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re: fclean all	
