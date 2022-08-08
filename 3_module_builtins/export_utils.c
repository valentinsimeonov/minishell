/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 12:32:29 by smischni          #+#    #+#             */
/*   Updated: 2022/08/07 19:38:13 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export_print(t_env *env, t_parser *parser)//PROBLEM: GOES IN LOOP!
{
	char	*values[2];
	t_env	*start;
	t_env	*smallest;
	int		output_fd;

	if (parser->output_fd > 2 || parser->output_fd == 1)
		output_fd = parser->output_fd;
	else
		output_fd = parser->pipe_fd[1];
	values[0] = ft_strdup("");
	values[1] = NULL;
	start = create_env_element(values);
	smallest = export_get_next_smallest(start, env);
	free(values[0]);
	free(start);
	while (smallest)
	{
		export_print_var(smallest, output_fd);
		smallest = export_get_next_smallest(smallest, env);
	}
	return (1);
}

t_env	*export_get_next_smallest(t_env *small, t_env *env)
{
	t_env	*next;
	t_env	*save;
	int		ln;

	save = env;
	ln = ft_strlen(small->bash_variable) + 1;
	while (env && ft_strncmp(small->bash_variable, env->bash_variable, ln) >= 0)
		env = env->next;
	if (!env)
		return (NULL);
	next = env;
	env = env->next;
	while (env)
	{
		ln = ft_strlen(env->bash_variable) + 1;
		if (ft_strncmp(env->bash_variable, small->bash_variable, ln) > 0)
		{
			if (ft_strncmp(env->bash_variable, next->bash_variable, ln) < 0)
				next = env;
		}
		env = env->next;
	}
	next = export_check_oldpwd(small, next, save);
	return (next);
}

t_env	*export_check_oldpwd(t_env *small, t_env *next, t_env *env)
{
	char	*values[2];

	if (ft_strncmp("OLDPWD", small->bash_variable, 7) > 0)
	{
		if (ft_strncmp("OLDPWD", next->bash_variable, 7) < 0)
		{
			values[0] = ft_strdup("OLDPWD");
			values[1] = NULL;
			return (create_env_element(values));
		}
	}
	if (ft_strncmp("OLDPWD", small->bash_variable, 7) == 0)
	{
		if (!get_env(env, "OLDPWD"))
		{
			free(small->bash_variable);
			free(small);
		}
	}
	return (next);
}

int	export_print_var(t_env *var, int output_fd)
{
	ft_putstr_fd("declare -x ", output_fd);
	ft_putstr_fd(var->bash_variable, output_fd);
	if (var->bash_v_content)
	{
		ft_putstr_fd("=\"", output_fd);
		ft_putstr_fd(var->bash_v_content, output_fd);
		ft_putchar_fd('"', output_fd);
	}
	ft_putchar_fd('\n', output_fd);
	return (1);
}
