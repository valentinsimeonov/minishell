/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:52:47 by smischni          #+#    #+#             */
/*   Updated: 2022/07/19 16:57:48 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	outfile(char *file, t_section *sec, t_shell *shell)
{
	int		flag_prv_file;
	char	*filename;
	
	//if previous outfile invalid, we return and don't open the current one
	if (sec->fd[1] < 0)
		return (0);
	//if there is a previous outfile, we close that one before we open a new one
	else if (sec->fd[1] > 2)
		close(sec->fd[1]);
	sec->fd[1] = -1;
	//remove > and space in front of the file name
	filename = trim_redirect(file, '>');//TBD
	//check if file exists, but isn't writeable
	if (!access(filename, F_OK) && access(filename, W_OK) < 0)
		//error Permission denied
	else
	{
		if(ft_strncmp(file, ">>", 2) == 0)
			sec->fd[1] = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else
			sec->fd[1] = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (sec->fd < 0)
			//error handling?? 
	}
	free(filename);
	return (0);
}
