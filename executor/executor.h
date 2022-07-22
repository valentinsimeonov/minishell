/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:37:06 by smischni          #+#    #+#             */
/*   Updated: 2022/07/22 19:04:13 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../minishell.h"

int		executor(t_parser *parser, t_env *env);
int		exec_section(t_list *sec, t_parser *parser, t_env *env);
int		exec_prep(t_list *sec, t_parser *parser);

int		is_infile(char *line);
int		infile(char *file, t_list *sec, t_parser *parser, char *filemode);
int		here_doc(char *lim);
int		open_infile(char *filename);

int		is_outfile(char *line);
int		outfile(char *file, t_list *sec, t_parser *parser, char *filemode);

int		create_command_array(int count, t_parser *parser, t_list *sec);
int		add_path(t_parser *parser);

int		free_str_array(char **str);
int		free_lst_array(t_list **lists);
char	**reassemble_env(t_env *env);

#endif