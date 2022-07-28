# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/29 14:19:05 by danisanc          #+#    #+#              #
#    Updated: 2022/07/26 15:53:23 by smischni         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c 1_module_env_builder/env_builder_for_parser1.c 1_module_env_builder/env_builder_for_parser2.c 1_module_env_builder/env_builder_standalone.c 2_module_parser/parser2.c 2_module_parser/parser1.c 2_module_parser/constructor.c 2_module_parser/env_handler1.c 2_module_parser/env_handler2.c 2_module_parser/final_command_builder1.c 5_module_signals/signals.c 4_module_executor/executor.c 4_module_executor/commands.c 4_module_executor/infile.c 4_module_executor/outfile.c 4_module_executor/utils.c

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -lreadline

LIB_LINUX = -lreadline

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

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
	$(RM) 1_module_env_builder/*.o
	$(RM) 2_module_parser/*.o
	$(RM) 4_module_executor/*.o
	$(RM) 5_module_signals/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a
	$(RM) 1_module_env_builder/*.o
	$(RM) 2_module_parser/*.o
	$(RM) 4_module_executor/*.o
	$(RM) 5_module_signals/*.o
	
re: fclean all

.PHONY: all bonus clean fclean re
