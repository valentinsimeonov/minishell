NAME = minishell

SRC = minishell.c

INCLUDE = minishell.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

RM = rm -f

all: $(NAME)

$(%.o): $(%.c)
	$(CC) -o $@ -c $^

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline $(OBJ)


clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re