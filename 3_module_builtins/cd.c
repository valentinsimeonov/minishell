/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:34 by smischni          #+#    #+#             */
/*   Updated: 2022/08/02 16:36:31 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd(t_env *env, t_parser *parser)
{
	if (!parser->command[1])
	{
		while (env)
		{
			if (ft_strncmp(env->bash_variable, "HOME", 5) == 0)
			{
				if (chdir(env->bash_v_content) < 0)
					return (0);//error handling, no such file or directory
				break;
			}
			else
				env = env->next;
		}
	}
	else
	{
		if (chdir(parser->command[1]) < 0)
			return (0);//error handling, no such file or directory
	}
	//CHANGE PWD && OLD_PWD IN ENV!!!!!
	return (1);
}
