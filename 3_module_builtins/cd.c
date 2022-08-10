/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:34 by smischni          #+#    #+#             */
/*   Updated: 2022/08/10 11:41:45 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_env *env, t_parser *parser, int flag_pipe)
{
	if (flag_pipe == 1)
		return (1);
	if (!parser->command[1])
	{
		if (cd_home(parser, env) == 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (chdir(parser->command[1]) < 0)
		{
			ft_error(parser, 1, parser->command[1], ": No such directory");
			return (0);
		}
	}
	cd_update_env(parser, env);
	return (1);
}

int	cd_home(t_parser *parser, t_env *env)
{
	t_env	*tmp;

	tmp = get_env(env, "HOME");
	if (!tmp || !tmp->bash_v_content)
	{
		ft_error(parser, 1, NULL, "cd: HOME not set");
		return (0);
	}
	if (chdir(tmp->bash_v_content) < 0)
	{
		ft_error(parser, 1, tmp->bash_v_content, ": No such directory");
		return (0);
	}
	return (1);
}

int	cd_update_env(t_parser *parser, t_env *env)
{
	t_env	*tmp;
	t_env	*pwd;
	char	*values[2];

	values[0] = ft_strdup("OLDPWD");
	values[1] = NULL;
	tmp = get_env(env, "OLDPWD");
	pwd = get_env(env, "PWD");
	if (!tmp)
	{
		ft_lstadd_back_env_element(&env, create_env_element(values));
		tmp = get_env(env, "OLDPWD");
	}
	if (tmp->bash_v_content)
		free(tmp->bash_v_content);
	tmp->bash_v_content = pwd->bash_v_content;
	pwd->bash_v_content = ft_calloc(PATH_MAX, sizeof(char));
	if (getcwd(pwd->bash_v_content, PATH_MAX) == NULL)
	{
		ft_error(parser, 1, "cd", "cd: getcwd failed");
		return (0);
	}
	return (1);
}
