/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/22 14:44:31 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * Iterates through every section (provided as an array of lists).
 * For each section, initializes file descriptors: input to STDIN, output to 
 * either STDOUT (for the last command section) or STDIN (for all command 
 * sections in front of pipes).
 * Then calls the preparation function exec_prep() and the execution function
 * exec_section() for every section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @return [int] 1 at success, 0 at failure.
*/
int	executor(t_parser *parser) //+env list
{
	t_list	**sections;
	t_list	*cur_sec;
	int		i;

	i = 0;
	sections = parser->sections;
	while (sections[i])
	{
		cur_sec = sections[i++];
		parser->input_fd = STDIN_FILENO;
		if (sections[i])
			parser->output_fd = STDIN_FILENO;
		else
			parser->output_fd = STDOUT_FILENO;
		if (exec_prep(cur_sec, parser) != 0)
			return (0);// error handling TBD
		exec_section(cur_sec, parser);
	}
	free_lst_array(parser->sections);
	return (1);
}

/**
 * Initializes file descriptors: input to STDIN, output to either STDOUT (for the
 * last command section) or STDIN (for all command sections in front of pipes).
 * Creates the command char** and opens potential in-/outfile with exec_prep().
 * Duplicates the input fd into STDIN to read the command input from there.
 * Creates a pipe and forks. TBD: checks for built-ins
 * In the child, duplicates the pipe's write-end into STDOUT, so the output is
 * written to pipe.
 * Duplicates the pipe's read end into the output fd.
 * @param sec [t_list *] List containing each word of the current input section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param flag_last [int] 1 if sec is the last section of the input. Else 0.
 * @return [int] 1 at success, 0 at failure.
*/
int	exec_section(t_list *sec, t_parser *parser) //+env list
{
	pid_t	pid;
	int		pipe_fd[2];

	if (dup2(parser->input_fd, STDIN_FILENO) < 0 || pipe(pipe_fd) < 0)
		return (0);// error handling TBD
	if (parser->input_fd > 2)//one-line function which tests?
		close(parser->input_fd);
	//OPEN: CHECK FOR BUILT-INS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	pid = fork();
	if (pid < 0)
		return (0);//error handling TBD
	if (pid == 0)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			return (0);//error handling TBD
		close(pipe_fd[1]);
		if (execve(parser->command[0], parser->command, parser->envp) < 0) //NEED ENVP!!!!
			return (0);//error handling TBD
	}
	waitpid(pid, NULL, 0);
	if (dup2(pipe_fd[0], parser->output_fd) < 0)
		return (0);//error handling TBD
	close(pipe_fd[0]);
	if (parser->output_fd > 2)//one-line function which tests?
		close(parser->output_fd);
	free_str_array(parser->command);
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