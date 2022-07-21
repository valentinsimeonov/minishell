/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/21 19:18:36 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * Iterates through every section (provided as an array of lists) and executes 
 * the commands in each section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @return [int] 1 at success, 0 at failure.
*/
int	executor(t_parser *parser)
{
	t_list	*cur_sec;
	int		i;

	i = 0;
	while (parser->sections[i] && parser->sections[i + 1])
	{
		cur_sec = parser->sections[i++];
		exec_section(cur_sec, parser);
	}
	exec_last_section();//TBD
	//free whole list / all variables in parser??
	return (1);
}

/**
 * Initializes file descriptors to STDIN & STDOUT.
 * Creates the command char** and opens potential in-/outfile with exec_prep().
 * Duplicates the input fd into STDIN, if there is an infile.
 * Creates a pipe and forks. TBD: checks for built-ins
 * In the child, duplicates the pipe's write-end into STDOUT, so the output is
 * written to pipe.
 * If there is an outfile, it duplicates the pipe's read end into the file.
 * Else, it duplicates it to STDIN to be used for the next command.
 * @param sec [t_list *] List containing each word of the current input section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @return [int] 1 at success, 0 at failure.
*/
int	exec_section(t_list *sec, t_parser *parser)
{
	pid_t	pid;
	int		pipe_fd[2];

	parser->input_fd = STDIN_FILENO;
	parser->output_fd = STDIN_FILENO;
	if (exec_prep(sec, parser) != 0)
		return (0);// error handling TBD
	if (parser->input_fd > 2)
	{
		if (dup2(parser->input_fd, STDIN_FILENO) < 0)
			return (0);// error handling TBD
		close(parser->input_fd);
	}
	if (pipe(pipe_fd) < 0)
		return (0);//error handling TBD
	//OPEN: CHECK FOR BUILT-INS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pid = fork();
	if (pid < 0)
		return (0);//error handling TBD
	if (pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			return (0);//error handling TBD
		close(pipe_fd[1]);
		if (execve(parser->command[0], parser->command, parser->envp) < 0)//NEED ENVP!!!!
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
	//free command array!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	return (1);
	//needs identifiers if child or parent i.e. for changing the env variables (ask Clemens)
}

/**
 * Checks all list elements of the current section. When it identifies in- or 
 * outfiles (signalized by <, <<, >> or >), it opens the respective file.
 * Counts the number non-file elements (ergo commands & commands) and calls a 
 * function to create a string array containing those.
 * @param sec [t_list *] List containing each word of the current input section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @return [int] 1 at success, 0 at failure.
*/
int	exec_prep(t_list *sec, t_parser *parser)
{
	int		count;
	t_list	*head;

	count = 0;
	head = sec;
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
