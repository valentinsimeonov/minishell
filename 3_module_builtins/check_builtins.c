/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:30:02 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 15:34:47 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_builtins(t_parser *parser, t_env *env)
{
	int	flag_pipe;

	flag_pipe = 0;
	if (parser->sections[1])
		flag_pipe = 1;
	if (ft_strncmp(parser->command[0], "cd", 3) == 0 && flag_pipe == 0)
		ft_cd(env, parser);
	else if (ft_strncmp(parser->command[0], "echo", 5) == 0)
		ft_echo(parser);
	else if (ft_strncmp(parser->command[0], "env", 4) == 0)
		ft_env(env, parser);
	else if (ft_strncmp(parser->command[0], "exit", 5) == 0 && flag_pipe == 0)
		ft_exit(env, parser);
	else if (ft_strncmp(parser->command[0], "export", 7) == 0 && flag_pipe == 0)
		ft_export(env, parser, parser->command);
	else if (ft_strncmp(parser->command[0], "pwd", 4) == 0)
		ft_pwd(parser);
	else if (ft_strncmp(parser->command[0], "unset", 6) == 0 && flag_pipe == 0)
		ft_unset(env, parser);
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
