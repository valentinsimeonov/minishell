/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:53:23 by smischni          #+#    #+#             */
/*   Updated: 2022/07/27 17:50:25 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(t_env *env, t_parser *parser)
{
	char	*tmp;
	char	*tmp2;

	if (parser->command[1])
		return (0);//error handling: "env: too many arguments"
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

int	ft_pwd(t_parser *parser)
{
	char	*buff;
	
	if (parser->command[1])
		return (0);//error handling: "pwd: too many arguments"
	buff = ft_calloc(PATH_MAX, sizeof(char));
	if (getcwd(buff, PATH_MAX) == NULL)
		return (0);//error handling ??
	ft_putstr_fd(buff, parser->output_fd);
	return (1);
}

int	ft_echo(t_parser *parser) //OPEN: print whitespaces between the string; 
{
	int	i;
	int	flag_nl;

	i = 1;
	flag_nl = 1;
	if (ft_strncmp(parser->command[i], "-n", 3) == 0)//multiple n's are also valid for the flag (-nnnnnn or -n -n)
	{
		flag_nl = 0;
		i++;
	}
	while (parser->command[i])
	{
		ft_putstr_fd(parser->command[i++], parser->output_fd);
		if (flag_nl == 1)
			ft_putchar_fd('\n', parser->output_fd);
	}
	return (1);
}
