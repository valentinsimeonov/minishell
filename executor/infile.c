/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:22:40 by smischni          #+#    #+#             */
/*   Updated: 2022/07/25 18:32:46 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * Checks if a string is identical to "<" or "<<" redirections. In that case, 
 * the following list element identifies either an infile or a heredoc delimiter.
 * @param line [char *] String to be checked for the redirection characters
 * @return [int] 1 if the string was identified as redirection, else 0.
*/
int	is_infile(char *line)
{
	if (ft_strncmp(line, "<", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "<<", 3) == 0)
		return (1);
	else
		return (0);
}

/**
 * Is called if file has been identified as infile or heredoc delimiter.
 * First, it checks if there was a previous, invalid infile - in that case, the
 * flag signals us to not actually use the current infile for input.
 * If there was a previous valid infile, the old one is closed.
 * Then, it diffentiates between a heredoc (<<) and calling the here_doc function
 * and a filename, for which a opening function would be called.
 * @param file [char *] Name of the infile or heredoc delimiter.
 * @param sec [t_list *] List containing each word of the current input section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param filemode [char *] String specifying if "file" is heredoc or filename.
 * @return [int] [int] 1 at success, 0 at failure.
*/
int	infile(char *file, t_list *sec, t_parser *parser, char *filemode)
{
	int		flag_prv_file;

	flag_prv_file = 0;
	if (parser->input_fd < 0)
		flag_prv_file = -1;
	else if (parser->input_fd > 2)
		close(parser->input_fd);
	if (ft_strncmp(filemode, "<<", 3) == 0)
		parser->input_fd = here_doc(file);
	else
		parser->input_fd = open_infile(file);
	if (flag_prv_file == -1 && parser->input_fd != -1)
	{
		close(parser->input_fd);
		parser->input_fd = -1;
	}
	return (0);
}

/**
 * Opens a temporary document and writes the command line input into it until
 * the delimiter string or the end of file (CTRL + D) is identified.
 * Then it opens the file again as input file for the following commands and
 * deletes it after closing the fd.
 * @param lim [char *] String representing the delimiter, which stops user input.
 * @return [int] Returns the fd of the open heredoc, or -1 in case of error.
*/
int	here_doc(char *lim)//do I need shell variables for error??
{
	char	*tmp;
	int		fd;

	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT, 0666);//should it be in another folder?
	if (fd < 0)
		return(fd);//error handling heredoc TBD
	while (1)
	{
		tmp = readline("> ");//needs -lreadline flag for compiling / TBD ob das zur history added??
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

/**
 * Checks if the file specified in filename is existant and readable.
 * If so, it opens the file and returns it's fd.
 * @param [char *] String containing the infile's name.
 * @return [int] Returns the fd of the open infile. In case of error, returns -1.
*/
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
