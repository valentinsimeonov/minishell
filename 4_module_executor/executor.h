/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:37:06 by smischni          #+#    #+#             */
/*   Updated: 2022/07/29 14:25:10 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"

typedef struct s_data t_data;
typedef struct s_parser t_parser;
typedef struct s_env t_env;

int		executor(t_data *data);
int		exec_prep(t_list *sec, t_parser *parser);
int		exec_section(t_parser *parser, t_env *env);
int		exec_last_section(t_parser *parser, t_env *env);

int		is_infile(char *line);
int		infile(char *file, t_parser *parser, char *filemode);
int		here_doc(char *lim);
int		open_infile(char *filename);

int		is_outfile(char *line);
int		outfile(char *file, t_parser *parser, char *filemode);

int		create_command_array(int count, t_parser *parser, t_list *sec);
int		add_path(t_parser *parser);

int		free_str_array(char **str);
int		free_lst_array(t_list **lists);
char	**reassemble_env(t_env *env);

//only for testing
int		print_all_input(t_data *data);

#endif