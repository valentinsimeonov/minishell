# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:19:05 by danisanc          #+#    #+#              #
#    Updated: 2022/05/29 16:03:04 by danisanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -lreadline

LIB_LINUX = -lreadline

#CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

#add $(CFLAGS) later, they are just annoying now
$(NAME): $(OBJ)
ifeq ($(UNAME_S), Darwin)
	$(MAKE) -C libft
	$(CC) $(OBJ) libft/libft.a $(LIB_MAC) -o $(NAME) 
else
	$(MAKE) -C libft
	$(CC) $(OBJ) libft/libft.a $(LIB_LINUX) -o $(NAME)
endif

clean:
	$(RM) *.o
	$(RM) libft/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
