/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/22 16:48:52 by smischni         ###   ########.fr       */
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
# include "lexar/lexar.h"
/* 2 Module Builtins */
# include "builtins/builtins.h"
/* Libft Library */
# include "libft/libft.h"



typedef struct s_variables
{
	// int			i;
	// int			j;
	int			arguments;
}			t_variables;

typedef struct s_env
{
	char			*bash_variable;
	char			*bash_v_content;
	struct s_env	*next;
}					t_env;

typedef struct s_parser
{
	t_list	**sections;//array of lists for each section, each list element is one part of the section
	int		input_fd;
	int		output_fd;
	char	**paths;
	char	**command;//string array to be handed over to execve. to be filled by Saskia
}				t_parser;

/* Temporary Palce for Function Prototypes (Will sort out Later) */
void	create_lexar(t_list *lexar_list, char **array);
int		size_of_array(char **array);
t_list	*create_stack_value(char **value);



#endif