/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:37:06 by smischni          #+#    #+#             */
/*   Updated: 2022/07/19 14:24:05 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
#define EXECUTOR_H

# include "../minishell.h"

int	infile(char *file, t_section *sec, t_shell *shell);
int	here_doc(char *lim);
int	open_infile(char *filename);

#endif