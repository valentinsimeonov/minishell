/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 11:57:33 by smischni         ###   ########.fr       */
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

int	exec_section(t_section *sec, t_shell *shell)
{
	if (exec_prep(sec, shell) != 0)
		//return (1); / error handling
	if (dup2(sec->fd[0], 0) < 0)
		//return (1); / error handling
	if (dup2(sec->fd[1], 1))
		//return (1); / error handling
	//Thoughts: Pipen nicht notwendig wenn keine weitere Section; was ist wenn outfile innerhalb der Section, wie umgehen mit der letzten Section??
	//forks
	//checks the command -> check for built-ins, else search in PATH for binary
	//needs identifiers if child or parent i.e. for changing the env variables (ask Clemens)
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
			infile(sec->split[i], sec, shell);
		else if (ft_strncmp(sec->split[i], ">", 1) == 0)
			outfile(sec->split[i], sec, shell);
		else
			count++;
		i++;
	}
	if (sec->fd[0] < 0 || sec->fd[1] < 0)
		//error handling; only display message of the first invalid infile and outfile
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
	return (0);
}
