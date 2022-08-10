

NAME = minishell

SRC = 	minishell.c \
		free.c \
		1_module_env_builder/env_builder_standalone.c \
		2_module_parser/parser2.c \
		2_module_parser/parser1.c \
		2_module_parser/constructor.c \
		2_module_parser/env_handler1.c \
		2_module_parser/env_handler2.c \
		2_module_parser/final_command_builder1.c \
		3_module_builtins/cd.c \
		3_module_builtins/check_builtins.c \
		3_module_builtins/echo.c \
		3_module_builtins/env.c \
		3_module_builtins/exit.c \
		3_module_builtins/export.c \
		3_module_builtins/export_utils.c \
		3_module_builtins/pwd.c \
		3_module_builtins/unset.c \
		4_module_executor/executor.c \
		4_module_executor/exec_utils.c \
		4_module_executor/commands.c \
		4_module_executor/file_utils.c \
		4_module_executor/infile.c \
		4_module_executor/outfile.c \
		4_module_executor/free_error.c \
		5_module_signals/signals.c

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

UNAME_S := $(shell uname -s)

LIB_MAC =  -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline

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
	$(RM) 3_module_builtins/*.o
	$(RM) 4_module_executor/*.o
	$(RM) 5_module_signals/*.o

fclean: clean
	$(RM) $(NAME)
	$(RM) libft/libft.a
	$(RM) 1_module_env_builder/*.o
	$(RM) 2_module_parser/*.o
	$(RM) 3_module_builtins/*.o
	$(RM) 4_module_executor/*.o
	$(RM) 5_module_signals/*.o
	
re: fclean all

.PHONY: all bonus clean fclean re
