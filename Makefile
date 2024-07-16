# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoizel <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/22 15:58:39 by aoizel            #+#    #+#              #
#    Updated: 2024/01/22 16:16:04 by wlalaoui         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

LIBFTPRINTF		=	libftprintf/libftprintf.a

LIBFTPRINTF_DIR	=	libftprintf/

INCLUDES		=	-I. -I./libftprintf/ft_printf/

LINKS			=	-L$(LIBFTPRINTF_DIR) -lftprintf -lreadline

CFLAGS 			=	-Wall -Wextra -Werror

CC 				=	cc $(CFLAGS)

SOURCES 		=	minishell.c \
					env_getset.c env_copy.c env_utils.c env_array_convert.c \
					check_error.c check_error2.c history.c quote_removal.c\
					parse_words.c parse_cmd.c parse_utils.c parse_spot.c parse_redir.c \
					parse_args.c parse_path.c string_expansion.c string_expansion2.c \
					string_expansion_main.c parse_pipes.c exec_processlst.c \
					clean_shell.c signal_handlers.c signal_handlers2.c exec_completion.c \
					exec_builtin.c bi_echo.c bi_cd.c bi_env.c bi_exit.c bi_export.c \
					bi_pwd.c bi_unset.c bi_export2.c

OBJECTS_DIR		=	.objs/

OBJECTS 		=	$(addprefix $(OBJECTS_DIR),$(SOURCES:.c=.o))

DEPENDENCIES	=	Makefile

MAKE			=	@make --no-print-directory


all:		$(OBJECTS_DIR) 
				$(MAKE) $(NAME)

$(NAME):	$(OBJECTS) | $(OBJECTS_DIR) $(LIBFTPRINTF)
				$(CC) $(OBJECTS) $(LINKS) $(INCLUDES) -o $(NAME)

$(OBJECTS_DIR):
				mkdir -p .objs

$(LIBFTPRINTF):
				$(MAKE) -C $(LIBFTPRINTF_DIR)

$(OBJECTS_DIR)%.o: %.c $(DEPENDENCIES)  $(LIBFTPRINTF)
				$(CC) -c $(INCLUDES) $< -o $@

$(OBJECTS_DIR)%.d: %.c | $(OBJECTS_DIR)
	$(CC) $< -MT $(OBJECTS_DIR)$(<:.c=.o) -MM -MP -MF $@

clean:
				$(MAKE) clean -C $(LIBFTPRINTF_DIR)
				rm -rf $(OBJECTS_DIR)

fclean:		clean
				$(MAKE) fclean -C $(LIBFTPRINTF_DIR)
				rm -rf $(NAME)

re:			fclean 
				make all

.PHONY: 	all clean fclean re

-include $(OBJECTS:.o=.d)
