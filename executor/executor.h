/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:37:06 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 17:01:29 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../minishell.h"

int	executor(t_parser *parser);
int	exec_section(t_list *sec, t_parser *parser);
int	exec_prep(t_list *sec, t_parser *parser);

int	infile(char *file, t_list *sec, t_parser *parser, char *filemode);

int	outfile(char *file, t_list *sec, t_parser *parser, char *filemode);

#endif