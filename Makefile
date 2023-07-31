# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iassafe <iassafe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/24 13:12:16 by khanhayf          #+#    #+#              #
#    Updated: 2023/07/28 12:15:03 by iassafe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

HEAD = minishell.h

SRC = minishell.c syntax+list_utils.c split.c syntax_utils.c split_utils.c expand.c expand1.c libft_utils.c ignore.c free.c exec_list.c open_files.c expand_hd.c libft.c

OBJ = minishell.o syntax+list_utils.o split.o syntax_utils.o split_utils.o expand.o expand1.o libft_utils.o ignore.o free.o exec_list.o open_files.o expand_hd.o libft.o

CC = cc

FLAGS = -Wall -Wextra -Werror -g
LIB =  -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

RM = rm -rf

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(LIB) -o $(NAME) $(OBJ) 

%.o : %.c $(HEAD)
	$(CC) $(FLAGS) -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
