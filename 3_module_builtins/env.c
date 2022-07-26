/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:53:23 by smischni          #+#    #+#             */
/*   Updated: 2022/07/26 17:29:58 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *env, t_parser *parser)
{
	char	*tmp;
	char	*tmp2;

	if (!env)
		return (0); //error handling tbd, is that even possible??
	while (env)
	{
		if (!env->bash_variable || env->bash_v_content)
			return (0); //error handling
		tmp = ft_strjoin(env->bash_variable, "=");
		tmp2 = ft_strjoin(tmp, env->bash_v_content);
		ft_putstr_fd(tmp2, parser->output_fd);
		free(tmp);
		free(tmp2);
		env = env->next;
	}
	return (1);
}

int	ft_pwd(t_env *env, t_parser *parser) //use cwd function??
{
	char	*tmp;
	
	if (!env)
		return (0); //error handling tbd, is that even possible??
	while (env)
	{
		tmp = env->bash_variable;
		if (ft_strncmp(tmp, "PWD", ft_strlen(tmp) + 1) == 0)
		{
			ft_putstr_fd(env->bash_v_content, parser->input_fd);
			return (1);
		}
		env = env->next;
	}
	return (0);//error handling tbd, PWD not found??
}
