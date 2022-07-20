/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:22:40 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 18:11:58 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_infile(char *line)
{
	if (ft_strncmp(line, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

int	infile(char *file, t_list *sec, t_parser *parser, char *filemode)//WIP
{
	int		flag_prv_file;
	
	flag_prv_file = 0;
	//if previous infile invalid, we open the new file but we don't use it for input
	if (parser->input_fd < 0)
		flag_prv_file = -1;
	//if there is a previous infile, we close that one before we open a new one
	else if (parser->input_fd > 2)
		close(parser->input_fd);
	//if it is a heredoc, we make file string the delimiter and call here_doc with it
	if (ft_strncmp(filemode, "<<", 3) == 0)
		parser->input_fd = here_doc(file);
	//else, we try to open the respective file
	else
		parser->input_fd = open_infile(file);
	//if the previous file was invilid but this one wasn't, we close this file again and set the fd back to -1 to signal the same to following files
	if (flag_prv_file == -1 && parser->input_fd != -1)
	{
		close(parser->input_fd);
		parser->input_fd = -1;
	}
	return (0);
}

int	here_doc(char *lim)//do I need shell variables for error??
{
	char	*tmp;
	int		fd;

	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT, 0666);//should it be in another folder?
	if (fd < 0)
		return(fd);//error handling heredoc TBD
	while (1)
	{
		tmp = readline("> ");//needs -lreadline flag for compiling
		if (!tmp || ft_memcmp(tmp, lim, ft_strlen(tmp)) == 0)
			break ;
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	if (tmp)
		free(tmp);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY | O_CREAT, 0666);//should it be in another folder?
	if (fd < 0)
		return(fd);//error handling heredoc TBD
	else
		unlink("/tmp/.heredoc");//should it be in another folder?
	return (fd);
}

int	open_infile(char *filename)//do I need shell variables for error?
{
	int	fd;

	fd = -1;
	if (!access(filename, F_OK))
	{
		if (!access(filename, R_OK))
			fd = open(filename, O_RDONLY);
		else
			return (-1);//error handling: no read permission
	}
	else
		return (-1);//error handling: no such file or directory
	return (fd);
	//TO-DO: only the error of the first invalid infile is displayed, implementation TBD
}
