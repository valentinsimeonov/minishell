/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/13 21:21:02 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//executes every section (separated by pipes) after another
int	executor(t_shell *shell)
{
	t_section	*cur_sec;

	while (shell->sections)
	{
		cur_sec = shell->sections->content; //requires libft to have a void pointer!!!
		//execute section
		shell->sections = shell->sections->next;
	}
	return (0);
}

int	exec_prep(t_section *sec, t_shell *shell)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	//initializing fds to STDIN & STDOUT in case there is no infile / outfile
	sec->fd[0] = STDIN_FILENO;
	sec->fd[1] = STDOUT_FILENO;
	/* checking if string is an in-/outfile or if it is a cmd / cmd argument
	   if it is a file (starting with > or <), it's opened (in case of multiple files, the last one is used)
	   else counting the number of cmd arguments to put them in a separate string array*/
	while (sec->split[i])
	{
		if (ft_strncmp(sec->split[i], "<", 1) == 0)
			infile(sec->split[i], sec, shell);//tbd
		else if (ft_strncmp(sec->split[i], ">", 1) == 0)
			outfile(sec->split[i], sec, shell);//tbd
		else
			count++;
		i++;
	}
	if (sec->fd[0] < 0 || sec->fd[1] < 0)
		//error handling
	sec->cmd = ft_calloc(count + 1, sizeof(char *));
	if (!sec->cmd)
		//error handling
	i = 0;
	// puts all strings that are not files in a separate command string array to be handed to execve.
	while (sec->split[i])
	{
		if (ft_strncmp(sec->split[i], "<", 1) != 0)
		{
			if (ft_strncmp(sec->split[i], ">", 1) != 0)
				sec->cmd[j] = ft_strdup(sec->split[i]);
		}
		i++;
	}
	//forks
	//checks the command -> check for built-ins, else search in PATH for binary
	//needs identifiers if child or parent i.e. for changing the env variables (ask Clemens)
}

int	infile(char *file, t_section *sec, t_shell *shell)
{
	int		flag_prv_file;
	char	*filename;
	
	flag_prv_file = 0;
	//if previous file invalid, we open the new file but we don't use it for input
	if (sec->fd[0] < 0)
		flag_prv_file = -1;
	//if there is a previous infile, we close that one before we open a new one
	else if (sec->fd[0] > 2)
		close(sec->fd[0]);
	//if it is a here_doc, we make the rest of the string the delimiter and call here_doc with it
	if (ft_strncmp(file, "<<", 2) == 0)
	{	
		filename = trim_redirect(file, '<');//tbd
		sec->fd[0] = here_doc(filename);
	}
	else
	{
		filename = trim_redirect(file, '<');//tbd
		sec->fd[0] = open_infile(filename);
	}
	if (flag_prv_file == -1)
		//close fd again, don't use it for input?? Set fd[0] back to STDIN?
	return (0);
}

int	here_doc(char *lim)//do I need shell variables for error??
{
	char	*tmp;
	int		fd[2];

	if (pipe(fd) < 0)//TO-DO: tmp doc statt pipe
	{
		ft_putstr_fd("ERROR:\npipe() failed in here_doc. 🚽\n", 2);
		return (-1);
	}
	while (1)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (!tmp || ft_memcmp(tmp, lim, ft_strlen(tmp)) == 0)
			break ;
		ft_putstr_fd(tmp, fd[1]);//TO-DO: tmp doc statt pipe
		free(tmp);
	}
	if (tmp)
		free(tmp);
	close(fd[1]);//TO-DO: tmp doc statt pipe
	return (fd[0]);
}

int	open_infile(char *filename)//do I need shell variables for error?
{
	int	fd;

	fd = -1;
	if (filename || ft_memcmp(filename, "", 1) == 0)
		//error handling - check if we parse empty arguments?
	else
	{
		if (!access(filename, F_OK))
		{
			if (!access(filename, R_OK))
				fd = open(filename, O_RDONLY);
			else
				//error handling: no read permission
		}
		else
			//error handling: no such file or directory
	}
	return (fd);
}
