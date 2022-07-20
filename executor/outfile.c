/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:52:47 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 18:10:01 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_outfile(char *line)
{
	if (ft_strncmp(line, ">", 2) == 0)
		return (1);
	else if (ft_strncmp(line, ">>", 3) == 0)
		return (1);
	else
		return (0);
}

int	outfile(char *file, t_list *sec, t_parser *parser, char *filemode)
{
	int		flag_prv_file;

	//if previous outfile invalid, we return and don't open the current one
	if (parser->output_fd < 0)
		return (0);
	//if there is a previous outfile, we close that one before we open a new one
	else if (parser->output_fd > 2)
		close(parser->output_fd);
	parser->output_fd = -1;
	//check if file exists, but isn't writeable
	if (!access(file, F_OK) && access(file, W_OK) < 0)
		return (0);//error handling TBD: Permission denied
	else
	{
		if(ft_strncmp(filemode, ">>", 3) == 0)
			parser->output_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			parser->output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (parser->output_fd < 0)
			return (0);//error handling TBD
	}
	return (1);
}
