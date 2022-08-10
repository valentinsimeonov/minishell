/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:42:32 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 17:58:35 by vsimeono         ###   ########.fr       */
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
# include </Users/vsimeono/goinfre/.brew/opt/readline/include/readline/readline.h>
# include </Users/vsimeono/goinfre/.brew/opt/readline/include/readline/history.h>
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
# include "4_module_executor/executor.h"
/* 5 Module Signals */
# include "5_module_signals/signals.h"

/*		Global Variable 		 */
extern int	g_exit_status;

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
	t_list	*pipe;
}			t_parser;

/* Main Struct Containing all other Structs */
typedef struct s_data
{
	t_parser	par;
	t_env		*to_env_list;
	t_list		*lexar;
	char		*line;

}				t_data;

/* Free */
void	ft_lstclear_env(t_env **lst, void (*del)(void *));
void	ft_lstdelone_env(t_env *lst, void (*del)(void *));

/* Main */
t_data	*initialiser(char **envp);

#endif