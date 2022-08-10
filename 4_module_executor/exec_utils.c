

#include "executor.h"

int	fork_section(t_parser *parser, t_env *env)
{
	pid_t		pid;
	int			status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_error(parser, 1, "fork", "fork_section: fork failed");
		return (0);
	}
	if (pid == 0)
	{
		if (child_section(parser, env) == 0)
			return (0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_parent);
	if (status > 0)
		g_exit_status = 128 + status;
	if (status == 0)
		g_exit_status = 0;
	return (1);
}

int	child_section(t_parser *parser, t_env *env)
{
	signal(SIGQUIT, SIG_DFL);
	if (parser->output_fd > 2 && dup2(parser->output_fd, STDOUT_FILENO) < 0)
	{
		ft_error(parser, 1, "dup2", "child_section: dup2 failed");
		return (0);
	}
	if (parser->output_fd < 3 && dup2(parser->pipe_fd[1], STDOUT_FILENO) < 0)
	{
		ft_error(parser, 1, "dup2", "child_section: dup2 failed");
		return (0);
	}
	close_pipe_fd(parser);
	execve(parser->command[0], parser->command, reassemble_env(env));
	ft_error(parser, 127, parser->command[0], ": command not found");
	exit(0);
}

int	fork_last_section(t_parser *parser, t_env *env)
{
	pid_t		pid;
	int			status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		ft_error(parser, 1, "fork", "fork_last_section: fork failed");
		return (0);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(parser->command[0], parser->command, reassemble_env(env));
		ft_error(parser, 127, parser->command[0], ": command not found");
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, signal_handler_parent);
	if (status > 0)
		g_exit_status = 128 + status;
	if (status == 0)
		g_exit_status = 0;
	return (1);
}

/**
 * Takes a list containing the environmental variables and reassembles it into
 * a string array, containing each variable as one string.
 * @param [t_env *] List containing each environmental variable as an element.
 * @return [char **] String array containing the environmental variables.
*/
char	**reassemble_env(t_env *env)
{
	t_env	*tmp;
	char	*tmp2;
	char	**envp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		tmp2 = ft_strjoin(env->bash_variable, "=");
		envp[i++] = ft_strjoin(tmp2, env->bash_v_content);
		free(tmp2);
		env = env->next;
	}
	return (envp);
}
