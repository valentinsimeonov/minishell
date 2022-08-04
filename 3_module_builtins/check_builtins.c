/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:30:02 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 16:54:55 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_builtins(t_parser *parser, t_env *env)
{
	int	flag_pipe;
	int	len;

	flag_pipe = 0;
	len = ft_strlen(parser->command[0]);
	if (parser->sections[1])
		flag_pipe = 1;
	dprintf(2, "commands[0] = %s\n", parser->command[0]);
	if (ft_strncmp(parser->command[0], "cd", len) == 0)
		ft_cd(env, parser, flag_pipe);
	else if (ft_strncmp(parser->command[0], "echo", len) == 0)
		ft_echo(parser);
	else if (ft_strncmp(parser->command[0], "env", len) == 0)
		ft_env(env, parser);
	else if (ft_strncmp(parser->command[0], "exit", len) == 0)
		ft_exit(env, parser, flag_pipe);
	else if (ft_strncmp(parser->command[0], "export", len) == 0)
		ft_export(env, parser, parser->command, flag_pipe);
	else if (ft_strncmp(parser->command[0], "pwd", len) == 0)
		ft_pwd(parser);
	else if (ft_strncmp(parser->command[0], "unset", len) == 0)
		ft_unset(env, parser, flag_pipe);
	else
		return (0);
	return (1);
}

t_env	*get_env(t_env *env, char *v_name)
{
	while (env)
	{
		if (ft_strncmp(env->bash_variable, v_name, ft_strlen(v_name) + 1) == 0)
		{
			return (env);
		}
		else
			env = env->next;
	}
	return (NULL);
}

t_env	*get_env_previous(t_env *env, char *v_name)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->bash_variable, v_name, ft_strlen(v_name) + 1) == 0)
			break ;
		tmp = tmp->next;
		count++;
	}
	if (count == 0)
		return (NULL);
	count--;
	while (count)
	{
		count--;
		env = env->next;
	}
	return (env);
}

int	is_builtin(char	*cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (ft_strncmp(cmd, "cd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", len) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", len) == 0)
		return (1);
	else
		return (0);
}
