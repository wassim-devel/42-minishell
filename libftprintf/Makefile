# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoizel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/16 09:30:09 by aoizel            #+#    #+#              #
#    Updated: 2024/01/09 13:17:44 by aoizel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			=	libftprintf.a

LIBFT_DIR 		=	libft/

PRINTF_DIR		=	ft_printf/

CFLAGS 			=	-Wall -Wextra -Werror

CC 				=	cc $(CFLAGS)

SOURCES_PRINTF	=	ft_printc.c ft_printf.c ft_prints.c ft_printx.c ft_getformat.c \
					ft_printd.c ft_printp.c ft_printu.c utilities.c

SOURCES_LIBFT	=	ft_toupper.c ft_bzero.c ft_strmapi.c ft_putchar_fd.c \
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

SOURCES			=	$(addprefix $(LIBFT_DIR),$(SOURCES_LIBFT)) \
					$(addprefix $(PRINTF_DIR),$(SOURCES_PRINTF))

OBJECTS 		=	$(SOURCES:.c=.o)

DEPENDENCIES	=	ft_printf/ft_printf.h libft/libft.h Makefile


all:		$(NAME)

$(NAME):	$(OBJECTS) $(DEPENDENCIES)
				ar -rc $@ $(OBJECTS)

%.o:		%.c $(DEPENDENCIES)
				$(CC) -c $< -I. -o $@ 

clean:
				rm -rf $(OBJECTS)

fclean:		clean
				rm -rf $(NAME)

re:			fclean 
				make all

.PHONY: 	all clean fclean re bonus
