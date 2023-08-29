# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 13:12:16 by khanhayf          #+#    #+#              #
#    Updated: 2023/08/19 12:21:26 by iassafe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

HEAD = minishell.h

SRC = minishell.c syntax+list_utils.c split.c syntax_utils.c split_utils.c \
	expand.c expand1.c libft_utils.c ignore.c free.c exec_list.c open_files.c \
	expand_hd.c libft.c builtins.c export.c echo_unset.c cd_with.c exit.c \
	cd_without.c ulist_env.c em_xec_env.c split_libft.c pipe.c pipe_utils.c \
	copy_env.c others.c signals.c expand2.c

OBJ = minishell.o syntax+list_utils.o split.o syntax_utils.o split_utils.o \
	expand.o expand1.o libft_utils.o ignore.o free.o exec_list.o open_files.o \
	expand_hd.o libft.o builtins.o export.o echo_unset.o cd_with.o exit.o \
	cd_without.o ulist_env.o em+xec_env.o split_libft.o pipe.o pipe_utils.o \
	copy_env.o others.o signals.o expand2.o

CC = cc

FLAGS = -Wall -Wextra -Werror
LIB =  -lreadline -L ~/.brew/opt/readline/lib 

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(LIB) -o $(NAME) $(OBJ)

%.o : %.c $(HEAD)
	$(CC) $(FLAGS) -I ~/.brew/opt/readline/include -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
