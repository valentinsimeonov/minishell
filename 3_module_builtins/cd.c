/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:34 by smischni          #+#    #+#             */
/*   Updated: 2022/08/02 18:27:40 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_env *env, t_parser *parser)//maybe to export first?? -> use for adding to env list
{
	t_env	*tmp;
	
	if (!parser->command[1])
	{
		tmp = get_env(env, "HOME")
		if (chdir(tmp->bash_v_content) < 0)
			return (0);//error handling, no such file or directory
	}
	else
	{
		if (chdir(parser->command[1]) < 0)
			return (0);//error handling, no such file or directory
	}
	tmp = get_env(env, "OLDPWD");
	if (!tmp)
		//add to env list -> ASK VALENTIN IF THERE IS A FUNCTION
	else
	{
		free(tmp->bash_v_content);
		tmp->bash_v_content = get_env(env, "PWD")->bash_v_content;
	}
	tmp = get_env(env, "PWD");
	tmp->bash_v_content = ft_calloc(PATH_MAX, sizeof(char));
	if (!getcwd(tmp->bash_v_content, PATH_MAX))
		return (0);//error handling tbd
	return (1);
}
