/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:52:47 by smischni          #+#    #+#             */
/*   Updated: 2022/07/26 14:53:55 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * Checks if a string is identical to ">" or ">>" redirections. In that case, 
 * the following list element identifies an outfile.
 * @param line [char *] String to be checked for the redirection characters
 * @return [int] 1 if the string was identified as redirection, else 0.
*/
int	is_outfile(char *line)
{
	if (ft_strncmp(line, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(line, ">>", 3) == 0)
		return (1);
	else
		return (0);
}

/**
 * Is called if there is an outfile to be opened with the name specified in file.
 * First, it checks if there was a previous, invalid outfile - in that case, the
 * new file is not opened.
 * If there was a previous valid outfile, the old one is closed.
 * Then, it checks whether the file already exists. If yes, it tries to write in
 * that file. Else, it opens a new file to write with the required access mode.
 * @param file [char *] Name of the file to be opened as outfile.
 * @param sec [t_list *] List containing each word of the current input section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param filemode [char *] String specifying the file access mode (> or >>).
 * @return [int] [int] 1 at success, 0 at failure.
*/
int	outfile(char *file, t_parser *parser, char *filemode)
{
	if (parser->output_fd < 0)
		return (0);
	else if (parser->output_fd > 2)
		close(parser->output_fd);
	parser->output_fd = -1;
	if (!access(file, F_OK) && access(file, W_OK) < 0)
		return (0);//error handling TBD: Permission denied
	else
	{
		if (ft_strncmp(filemode, ">>", 3) == 0)
			parser->output_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			parser->output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (parser->output_fd < 0)
			return (0);//error handling TBD
	}
	return (1);
}
