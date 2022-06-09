/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/07 19:07:48 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> /// For Open 
# include <signal.h>  /// For Signals
# include <sys/wait.h>  /// For Wait
# include <readline/readline.h>  /// For Readline
# include <readline/history.h>  /// For History
# include <sys/stat.h>  /// For lstats
// # include <sys/types.h> /// TODO V - Can't remember what I did here

/* 1 Module Lexar */
# include "1_module_lexar/lexar.h"
/* 2 Module Builtins */
# include "2_module_builtins/builtins.h"
/* Libft Library */
# include "libft/libft.h"



typedef struct s_parser
{
	char	*command;
	char	*arg;
	char	*input_file;	     //   - Input File < In File
	char 	*input_heredoc;      //	  - Input File << Here Doc
	char	*output_truncate;    //	  - Outputs Truncate
	char	*output_append;	     //   - Outputs Append
	char	*err_file;           //   - Error File (Second > )
}			t_parser;

typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	struct s_env	*next;
}	t_env;

typedef struct s_all 
{
	t_parser to_parser_list;
	t_env	to_env_list;
}	t_all;


/* Temporary Place for Function Prototypes (Will sort out Later) */

	/* 1 Module Lexar */
int		lexar(t_list **lexar_list, char *line);
static int	create_lexar_list(char *line, t_list **lexar_list, int *start, int *end);   
int		size_of_array(char **array);
static void	finding_last_quote(char *line, int *end);

static int	remove_quotes(char **str);
char	*remove_char(char *str, int index);
int		is_invisible(int c);
int		is_special_char(int c);
static void	is_file_sign(char *line, int *end);


	/*  Module Parser */
void	is_d_quotes_closed(t_list *lexar_list);


	/* Linked Lists Utils */
t_list	*create_element(char **value);
void	print_list(t_list **stack);
void	free_list(t_list **list);
void	delete_list(t_list **list);

	/*		ENV List	*/
// t_env		create_env_list(char	**envp);
void	create_env_list(char	**envp);
t_env	*create_env_element(char **value);
void	ft_lstadd_back_env_element(t_env **lst, t_env *new);
void	print_env_list(t_env **stack);


#endif