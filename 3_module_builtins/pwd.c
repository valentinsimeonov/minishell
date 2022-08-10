/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:48:05 by smischni          #+#    #+#             */
/*   Updated: 2022/08/10 15:00:29 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_parser *parser)
{
	char	*buff;
	int		output_fd;

	if (parser->output_fd > 2 || parser->output_fd == 1)
		output_fd = parser->output_fd;
	else
		output_fd = parser->pipe_fd[1];
	buff = ft_calloc(PATH_MAX, sizeof(char));
	if (getcwd(buff, PATH_MAX) == NULL)
	{
		ft_error(parser, 1, "pwd", "pwd: getcwd failed");
		return (0);
	}
	ft_putstr_fd(buff, output_fd);
	ft_putchar_fd('\n', output_fd);
	free(buff);
	return (1);
}
