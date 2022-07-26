/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:30:02 by smischni          #+#    #+#             */
/*   Updated: 2022/07/25 19:36:42 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_builtins(t_parser *parser, t_env *env)
{
	if (ft_strncmp(parser->command[0], "cd", ft_strlen(parser->command[0] + 1))
		//call cd function & return (1)
	else if (ft_strncmp(parser->command[0], "echo", ft_strlen(parser->command[0] + 1))
		//call echo function
	else if (ft_strncmp(parser->command[0], "env", ft_strlen(parser->command[0] + 1))
		//call env function
	else if (ft_strncmp(parser->command[0], "exit", ft_strlen(parser->command[0] + 1))
		//call exit function
	else if (ft_strncmp(parser->command[0], "export", ft_strlen(parser->command[0] + 1))
		//call export function
	else if (ft_strncmp(parser->command[0], "pwd", ft_strlen(parser->command[0] + 1))
		//call pwd function
	else if (ft_strncmp(parser->command[0], "unset", ft_strlen(parser->command[0] + 1))
		//call unset function
	else
		return (0);
	return (1);
}
