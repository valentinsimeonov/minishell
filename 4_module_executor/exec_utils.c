/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 21:01:03 by smischni          #+#    #+#             */
/*   Updated: 2022/08/09 21:49:16 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	fork_section(t_parser *parser, t_env *env)
{
	pid_t		pid;
	int			status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_error(1, "fork", "fork_section: fork failed");//freeing/closing?
		return (0);
	}
	if (pid == 0)
	{
		if (child_section(parser, env) == 0)//freeing/closing?
			return (0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_parent);
	if (status > 0)
		global_exit_status = 128 + status;
	if (status == 0)
		global_exit_status = 0;
	return (1);
}

int	child_section(t_parser *parser, t_env *env)
{
	signal(SIGQUIT, SIG_DFL);
	if (parser->output_fd > 2 && dup2(parser->output_fd, STDOUT_FILENO) < 0)
	{
		ft_error(1, "dup2", "child_section: dup2 failed");//freeing/closing?
		return (0);
	}
	if (parser->output_fd < 3 && dup2(parser->pipe_fd[1], STDOUT_FILENO) < 0)
	{
		ft_error(1, "dup2", "child_section: dup2 failed");//freeing/closing?
		return (0);
	}
	close_pipe_fd(parser->pipe_fd);
	execve(parser->command[0], parser->command, reassemble_env(env));
	ft_error(127, parser->command[0], ": command not found");
	//freeing/closing?
	exit(0);
}

int	fork_last_section(t_parser *parser, t_env *env)//TBD
{
	pid_t		pid;
	int			status;

	status = 0;
	pid = fork();
	if (pid < 0)
		return (0);//error handling TBD
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(parser->command[0], parser->command, reassemble_env(env));
		ft_error(127, parser->command[0], ": command not found");
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_parent);
	if (status > 0)
		global_exit_status = 128 + status;
	if (status == 0)
		global_exit_status = 0;
	return (1);
}
