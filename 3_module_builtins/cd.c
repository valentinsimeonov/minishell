/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:34 by smischni          #+#    #+#             */
/*   Updated: 2022/08/09 17:29:29 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_env *env, t_parser *parser, int flag_pipe)
{
	t_env	*tmp;

	if (flag_pipe == 1)
		return (1);
	if (!parser->command[1])
	{
		tmp = get_env(env, "HOME");
		if (chdir(tmp->bash_v_content) < 0)
			return (0);//error handling, no such file or directory
	}
	else
	{
		if (chdir(parser->command[1]) < 0)
			return (0);//error handling, no such file or directory
	}
	cd_update_env(env);
	return (1);
}

int	cd_update_env(t_env *env)
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
		return (0);//error handling ??
	return (1);
}
