
#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> /// For Open 
# include <signal.h>  /// For Signals
# include <sys/wait.h>  /// For Wait
# include </Users/vsimeono/goinfre/.brew/opt/readline/include/readline/readline.h>  /// For Readline
# include </Users/vsimeono/goinfre/.brew/opt/readline/include/readline/history.h>  /// For History
# include <sys/stat.h>  /// For Using WEXITSTATUS
# include <limits.h> //for PATH_MAX
/* Libft Library */
# include "libft/libft.h"
/* 1 Module ENV Builder */
# include "1_module_env_builder/env_builder.h"
/* 2 Module Lexar */
# include "2_module_parser/parser.h"
/* 3 Module Builtins */
# include "3_module_builtins/builtins.h"
/* 4 Module Executor */
#include "4_module_executor/executor.h"
/* 5 Module Signals */
#include "5_module_signals/signals.h"

/*		Global Variable 		 */
extern int global_exit_status;

/*      ENV Builder Standalone   */
typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	struct s_env	*next;
}					t_env;

/*     Parsed Command List      */
typedef struct s_parser
{
	t_list	**sections;
	int		input_fd;
	int		output_fd;
	int		store_stdin;
	int		store_stdout;
	int		pipe_fd[2];
	char	**paths;
	char	**command;
}			t_parser;

/* Main Struct Containing all other Structs */
typedef struct s_data
{
	t_parser	to_parser_list;
	t_env		*to_env_list;
	t_list		*lexar_list;
}				t_data;

/* Temporary Place for Function Prototypes (Will sort out Later) */
void	free_minishell(t_data *data);
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
void	ft_lstdelone_env(t_env *lst, void (*del)(void *));

/* Main */
t_data	*env_builder(char **envp);


/*  Module Parser */
void	is_d_quotes_closed(t_list *lexar_list);

/* Linked Lists Utils */
t_list	*create_element(char *value);
void	print_list(t_list **stack);
void	free_list(t_list **list);
void	delete_list(t_list **list);

/*		ENV List	*/
// t_env		create_env_list(char	**envp);
t_env	*create_env_list(char	**envp);
t_env	*create_env_element(char **value);
void	ft_lstadd_back_env_element(t_env **lst, t_env *new);
void	print_env_list(t_env **stack);

/* Module Signals */
void	signal_check(t_data *data);


#endif