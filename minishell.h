/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/05 15:52:44 by smischni         ###   ########.fr       */
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

/* Saskia: Suggested structs */
typedef struct s_shell //contains all variables necessary for our project, to be extended
{
	char	**env; // handover all env variables between functions
	char	**path; // handover a char containing all possible paths, necessary for execution
	int	nbr_sections; // number of sections separated by pipes (if 1, no piping necessary)
	t_list	*sections; //list or array of section structs -> requires t_list to have a void pointer!!!
}				t_shell;

typedef struct s_section
{
	char	*raw;//containing the raw string of the section (optional)
	char	**split;//containing the string of the section parsed by spaces (except stuff that is in quotes and not after redirections)
	int		fd[2];//fds for input and output; initialized to STDIN & STDOUT, only changed by me if there are redirections
}				t_section;


/* Temporary Palce for Function Prototypes (Will sort out Later) */
void	create_lexar(t_list *lexar_list, char **array);
int		size_of_array(char **array);
t_list	*create_stack_value(char **value);



#endif