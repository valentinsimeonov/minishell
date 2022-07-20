/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:37:06 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 18:16:18 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../minishell.h"

int	executor(t_parser *parser);
int	exec_section(t_list *sec, t_parser *parser);
int	exec_prep(t_list *sec, t_parser *parser);
int	create_command_array(int count, t_parser *parser, t_list *sec);

int	is_infile(char *line);
int	infile(char *file, t_list *sec, t_parser *parser, char *filemode);
int	here_doc(char *lim);
int	open_infile(char *filename);

int	is_outfile(char *line);
int	outfile(char *file, t_list *sec, t_parser *parser, char *filemode);

#endif