/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/31 21:57:46 by vsimeono         ###   ########.fr       */
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



typedef struct s_variables
{
	// int			i;
	// int			j;
	int			arguments;
}			t_variables;

typedef struct s_env
{
	char	*pwd;
	char	*old_pwd;
} t_env;


/* Temporary Place for Function Prototypes (Will sort out Later) */

/* 1 Module Lexar */
// void	create_lexar(t_list *lexar_list, char **array);   
void	create_lexar(t_list *lexar_list, char *line);   

int		size_of_array(char **array);

	/* Linked Lists Utils */
t_list	*create_element(char **value);
void	print_list(t_list **stack);
void	free_list(t_list **list);
void	delete_list(t_list **list);

/*				ENV List			*/
t_env		create_env_list(char	**envp);

#endif