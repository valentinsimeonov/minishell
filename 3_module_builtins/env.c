/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:53:23 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 15:43:02 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *env, t_parser *parser)
{
	char	*tmp;
	char	*tmp2;

	if (parser->command[1])
		return (0);//error handling: "env: too many arguments"?
	if (!env)
		return (0); //error handling tbd, is that even possible??
	while (env)
	{
		if (env->bash_v_content)
		{
			tmp = ft_strjoin(env->bash_variable, "=");
			tmp2 = ft_strjoin(tmp, env->bash_v_content);
			ft_putstr_fd(tmp2, parser->output_fd);
			ft_putchar_fd('\n', parser->output_fd);
			free(tmp);
			free(tmp2);
		}
		env = env->next;
	}
	return (1);
}
