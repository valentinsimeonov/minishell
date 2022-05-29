/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:07 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/29 11:24:05 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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
#include "lexar.h"

/* 2 Module Builtins */
#include "builtins.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
} t_list;

typedef struct s_variables
{
	// int			i;
	// int			j;
	int			arguments;
}

char		*readline(const char *);

#endif