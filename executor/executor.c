/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/05 16:06:41 by smischni         ###   ########.fr       */
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

int	exec_sec(t_section *sec)
{
	//looks for in and outfiles, and initializes the fds accordingly / opens here_doc
	//TO-DO: check what happens with multiple in and outfiles per section (outfile always the latter?)
	//puts everything else in a cmd string (Open: what if stuff is separated by files?)
	//forks
	//checks the command -> check for built-ins, else search in PATH for binary
	//needs identifiers if child or parent i.e. for changing the env variables (ask Clemens)
}
