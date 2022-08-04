/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:53:23 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 20:42:33 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *env, t_parser *parser)
{
	char	*tmp;
	char	*tmp2;
	int		output_fd;

	if (parser->command[1])
		return (0);//error handling: "env: too many arguments"?
	if (parser->pipe_fd[1] != -1)
		output_fd = parser->pipe_fd[1];
	else
		output_fd = parser->output_fd;
	while (env)
	{
		if (env->bash_v_content)
		{
			tmp = ft_strjoin(env->bash_variable, "=");
			tmp2 = ft_strjoin(tmp, env->bash_v_content);
			ft_putstr_fd(tmp2, output_fd);
			ft_putchar_fd('\n', output_fd);
			free(tmp);
			free(tmp2);
		}
		env = env->next;
	}
	return (1);
}
