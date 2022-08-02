/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:48:05 by smischni          #+#    #+#             */
/*   Updated: 2022/08/02 15:48:24 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_parser *parser)
{
	char	*buff;
	
	if (parser->command[1])
		return (0);//error handling: "pwd: too many arguments"
	buff = ft_calloc(PATH_MAX, sizeof(char));
	if (getcwd(buff, PATH_MAX) == NULL)
		return (0);//error handling ??
	ft_putstr_fd(buff, parser->output_fd);
	free(buff);
	return (1);
}
