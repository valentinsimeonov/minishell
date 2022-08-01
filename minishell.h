
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
# include <sys/stat.h>  /// For lstats
# include <limits.h> //for PATH_MAX
/* Libft Library */
# include "libft/libft.h"
/* 1 Module ENV Builder */
# include "1_module_env_builder/env_builder.h"
/* 2 Module Lexar */
# include "2_module_parser/parser.h"
/* 5 Module Signals */
#include "5_module_signals/signals.h"
/* Module Executor */
#include "4_module_executor/executor.h"


/*		Global Variable 		 */
extern int global_exit_status;

/*      ENV Builder Standalone   */
typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	struct s_env	*next;
}					t_env;

/*      ENV Builder For Parser   */
typedef struct s_envp_data
{
	t_list	**envp_cp;
	t_list	**envp_empty;
	t_list	*pwd_list;
	t_list	*old_pwd_list;
	char	*pwd;
	char	*old_pwd;
	int		exit_status;
}				t_envp_data;

/*     Parsed Command List      */
typedef struct s_parser
{
	t_list	**sections;
	int		input_fd;
	int		output_fd;
	char	**paths;
	char	**command;
}			t_parser;

/* Main Struct Containing all other Structs */
typedef struct s_data
{
	t_parser	to_parser_list;
	t_env		to_env_list;
	t_envp_data	to_envp_data;
}				t_data;

// typedef struct s_list
// {
// 	char			*line;
// 	struct s_list	*next;
// }				t_list;


// /* Saskia: Suggested structs */
// typedef struct s_shell //contains all variables necessary for our project, to be extended
// {
// 	char	**env; // handover all env variables between functions
// 	char	**path; // handover a char containing all possible paths, necessary for execution
// 	int		nbr_sections; // number of sections separated by pipes (if 1, no piping necessary)
// 	t_list	*sections; //list or array of section structs -> requires t_list to have a void pointer!!!
// }				t_shell;

// typedef struct s_section
// {
// 	char	*raw;//containing the raw string of the section (optional) 
// 	char	**split;//containing the string of the section parsed by spaces (except stuff that is in quotes and not after redirections)
// 	int		fd[2];//fds for input and output; initialized to STDIN & STDOUT, only changed by me if there are redirections
// 	char	**cmd;//containig the command and all its arguments, initialized by me
// }				t_section;



/* Example:
< colors.txt sort | uniq -c | sort -r | head -3 > favcolors.txt
section[0]:
split = {"< colors.txt", "sort"}
section[1]:
split = {"uniq", "-c"}
section[2]:
split = {"sort", "-r"}
section[3]:
split = {"head", "-3", "> favcolors.txt"} */


// /* Global Variable */
// extern int	g_pid;

/* Temporary Place for Function Prototypes (Will sort out Later) */

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
