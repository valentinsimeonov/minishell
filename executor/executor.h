/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:37:06 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 10:55:01 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../minishell.h"

int		executor(t_shell *shell);
int		exec_prep(t_section *sec, t_shell *shell);

int		infile(char *file, t_section *sec, t_shell *shell);
int		here_doc(char *lim);
int		open_infile(char *filename);

int		outfile(char *file, t_section *sec, t_shell *shell);

char	*trim_redirect(char *file, char c);

#endif