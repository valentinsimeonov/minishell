#include "executor.h"

/**
 * Iterates through every section (provided as an array of lists).
 * For each section, initializes file descriptors: input to STDIN, output to 
 * either STDOUT (for the last command section) or STDIN (for all command 
 * sections in front of pipes).
 * Then calls the preparation function exec_prep() and the execution function
 * exec_section() for every section.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param env [t_env *] List of environment variables.
 * @return [int] 1 at success, 0 at failure.
*/
int	executor(t_data *data)
{
	t_list		*cur_sec;
	int			i;
	t_parser	*parser;

	i = 0;
	parser = &(data->to_parser_list);
	store_fds(parser);
	while (parser->sections[i])
	{
		cur_sec = parser->sections[i++];
		parser->input_fd = STDIN_FILENO;
		if (parser->sections[i])
			parser->output_fd = STDIN_FILENO;
		else
			parser->output_fd = STDOUT_FILENO;
		if (exec_prep(cur_sec, parser) == 0)
			return (0);// error handling TBD
		//print_all_input(data);//TEST INPUT
		if (parser->sections[i])
			exec_section(data);
		else
			exec_last_section(data);
	}
	restore_std_fds(parser);
	free_lst_array(parser->sections);
	//free path? -> @Valentin: do you recreate the path from the env list with every input?
	return (1);
}

/**
 * Checks all list elements of the current section. When it identifies in- or 
 * outfiles (signalized by <, <<, >> or >), it opens the respective file.
 * Counts the number non-file elements (ergo commands & options) and calls a 
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
			infile((char *)head->next->line, parser, (char *)head->line);
			head = head->next;
		}
		else if (is_outfile(head->line) == 1 && head->next)
		{
			outfile((char *)head->next->line, parser, (char *)head->line);
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

/**
 * Duplicates the input fd into STDIN to read the command input from there.
 * Creates a pipe and forks. TBD: checks for built-ins
 * In the child, duplicates the pipe's write-end into STDOUT, so the output is
 * written to pipe.
 * Duplicates the pipe's read end into the output fd.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param env [t_env *] List of environment variables.
 * @return [int] 1 at success, 0 at failure.
*/
int	exec_section(t_data *data)
{
	pid_t		pid;
	int			status;
	t_parser	*parser;
	t_env		*env;

	status = 1;
	parser = &data->to_parser_list;
	env = data->to_env_list;
	if (pipe(parser->pipe_fd) < 0)
		return (0);//error handling tbd
	if (parser->input_fd > 2 && dup2(parser->input_fd, STDIN_FILENO) < 0)
		return (0);//error handling tbd
	if (check_builtins(data) == 0)
	{
		pid = fork();
		if (pid < 0)
			return (0);//error handling TBD
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);

			if (parser->output_fd > 2 && dup2(parser->output_fd, STDOUT_FILENO) < 0)
				return (0);//error handling TBD
			if (parser->output_fd < 3 && dup2(parser->pipe_fd[1], STDOUT_FILENO) < 0)
				return (0);//error handling TBD
			close_pipe_fd(parser->pipe_fd);
			execve(parser->command[0], parser->command, reassemble_env(env));
			//error handling: command not found
			return (0);//error handling TBD
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler_parent);
		if (status > 0)
			global_exit_status = 128 + status;
		if (status == 0)
			global_exit_status = 0;
	}
	if (parser->output_fd < 3 && dup2(parser->pipe_fd[0], parser->output_fd) < 0)
		return (0);//error handling TBD
	close_pipe_fd(parser->pipe_fd);
	if (parser->output_fd > 2)
		close(parser->output_fd);
	free_str_array(parser->command);
	return (1);
}

/**
 * Duplicates the input fd into STDIN to read the command input from there.
 * Creates a pipe and forks. TBD: checks for built-ins
 * In the child, duplicates the pipe's write-end into STDOUT, so the output is
 * written to pipe.
 * Duplicates the pipe's read end into the output fd.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param env [t_env *] List of environment variables.
 * @return [int] 1 at success, 0 at failure.
*/
int	exec_last_section(t_data *data)
{
	pid_t		pid;
	int			status;
	t_parser	*parser;
	t_env		*env;

	parser = &data->to_parser_list;
	env = data->to_env_list;
	status = 1;
	if (dup2(parser->input_fd, STDIN_FILENO) < 0)
		return (0);// error handling TBD
	if (dup2(parser->output_fd, STDOUT_FILENO) < 0)
		return (0);// error handling TBD
	if (check_builtins(data) == 0)
	{
		pid = fork();
		if (pid < 0)
			return (0);//error handling TBD
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			execve(parser->command[0], parser->command, reassemble_env(env));
			//error handling: command not found
			exit(127);//error handling TBD
		}
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler_parent);
		if (status > 0)
			global_exit_status = 128 + status;
		if (status == 0)
			global_exit_status = 0;
	}
	if (parser->input_fd > 2)
		close(parser->input_fd);
	if (parser->output_fd > 2)	
		close(parser->output_fd);
	free_str_array(parser->command);
	return (1);
}
