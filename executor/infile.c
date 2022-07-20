/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 14:22:40 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 11:04:53 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	infile(char *file, t_section *sec, t_shell *shell)
{
	int		flag_prv_file;
	char	*filename;
	
	flag_prv_file = 0;
	//if previous infile invalid, we open the new file but we don't use it for input
	if (sec->fd[0] < 0)
		flag_prv_file = -1;
	//if there is a previous infile, we close that one before we open a new one
	else if (sec->fd[0] > 2)
		close(sec->fd[0]);
	//remove < and space in front of the file name
	filename = trim_redirect(file, '<');
	//if it is a heredoc, we make the rest of the string the delimiter and call here_doc with it
	if (ft_strncmp(file, "<<", 2) == 0)
		sec->fd[0] = here_doc(filename);
	//else, we try to open the respective file
	else
		sec->fd[0] = open_infile(filename);
	//if the previous file was invilid but this one wasn't, we close this file again and set the fd back to -1 to signal the same to following files
	if (flag_prv_file == -1 && sec->fd[0] != -1)
	{
		close(sec->fd[0]);
		sec->fd[0] = -1;
	}
	free(filename);
	return (0);
}

int	here_doc(char *lim)//do I need shell variables for error??
{
	char	*tmp;
	int		fd;

	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT, 0666);//should it be in another folder?
	if (fd < 0)
		//error handling heredoc
	while (1)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
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
		//error handling heredoc
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
			//error handling: no read permission
	}
	else
		//error handling: no such file or directory
	return (fd);
	//TO-DO: only the error of the first invalid infile is displayed, implementation TBD
}
