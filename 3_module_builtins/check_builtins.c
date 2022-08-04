/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:30:02 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 12:38:10 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_builtins(t_parser *parser, t_env *env)
{
	//TO-DO: some are not executed when pipes
	if (ft_strncmp(parser->command[0], "cd", 3) == 0)
		//call cd function
	else if (ft_strncmp(parser->command[0], "echo", 5) == 0)
		ft_echo(parser);
	else if (ft_strncmp(parser->command[0], "env", 4) == 0)
		ft_env(env, parser);
	else if (ft_strncmp(parser->command[0], "exit", 5) == 0)
		//call exit function
	else if (ft_strncmp(parser->command[0], "export", 7) == 0)
		ft_export(env, parser, parser->command);
	else if (ft_strncmp(parser->command[0], "pwd", 4) == 0)
		ft_pwd(parser);
	else if (ft_strncmp(parser->command[0], "unset", 6) == 0)
		//call unset function
	else
		return (0);
	return (1);
}
