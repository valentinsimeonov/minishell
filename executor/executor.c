/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/21 17:28:23 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//executes every section (separated by pipes) after another
int	executor(t_parser *parser)
{
	t_list	*cur_sec;
	int		i;

	i = 0;
	while (parser->sections[i] && parser->sections[i + 1])
	{
		cur_sec = parser->sections[i++];
		if (exec_section(cur_sec, parser) != 0)
			return (0);//error handling tbd
	}
	exec_last_section();//TBD
	//free whole list / all variables in parser??
	return (0);
}

int	exec_section(t_list *sec, t_parser *parser)
{
	pid_t	pid;
	int		pipe_fd[2];

	//initializing fds to STDIN & STDOUT in case there is no infile / outfile
	parser->input_fd = STDIN_FILENO;
	parser->output_fd = STDIN_FILENO;
	//prepare the command string array and open in-/outfiles
	if (exec_prep(sec, parser) != 0)
		return (0);// error handling TBD
	//if there is an infile, duplicate that one into STDIN
	if (parser->input_fd > 2)
	{
		if (dup2(parser->input_fd, STDIN_FILENO) < 0)
			return (0);// error handling TBD
		close(parser->input_fd);
	}
	//Create a pipe
	if (pipe(pipe_fd) < 0)
		return (0);//error handling TBD
	//OPEN: CHECK FOR BUILT-INS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//fork to create a child process for executing a binary
	pid = fork();
	if (pid < 0)
		return (0);//error handling TBD
	//condition only executed by child process, executes the binary and then dies
	if (pid == 0)
	{
		if(dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			return (0);//error handling TBD
		close(pipe_fd[1]);
		if (execve(parser->command[0], parser->command, parser->envp))//NEED ENVP!!!!
			return (0);//error handling TBD
	}
	waitpid(pid, NULL, 0);
	if (parser->output_fd > 2)
	{
		if (dup2(pipe_fd[0], parser->output_fd) < 0)
			return (0);//error handling TBD
	}
	else
	{
		if (dup2(pipe_fd[0], STDIN_FILENO) < 0)
			return (0);//error handling TBD	
	}
	return (1);
	//needs identifiers if child or parent i.e. for changing the env variables (ask Clemens)
}

int	exec_prep(t_list *sec, t_parser *parser)
{
	int		count;
	t_list	*head;

	count = 0;
	head = sec;
	//checking list elements:
	//if > or >> the next element is an infile
	//if < or << the next element is an outfile
	//else it is counted as a command to allocate enough memore for char **command
	while (head)
	{
		if (is_infile(head->line) == 1 && head->next)
		{
			infile(head->next->line, sec, parser, head->line);
			head = head->next;
		}
		else if (is_outfile(head->line) == 1 && head->next)
		{
			outfile(head->next->line, sec, parser, head->line);
			head = head->next;
		}
		else
			count++;
		head = head->next;
	}
	if (parser->input_fd < 0 || parser->output_fd < 0)
		return (0);//error handling TBD; only display message of the first invalid infile and outfile
	create_command_array(count, parser, sec); //error handling??
	return (1);
}
