/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:29:14 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 19:39:03 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_parser *parser)
{
	int	output_fd;

	if (parser->pipe_fd[1] != -1)
		output_fd = parser->pipe_fd[1];
	else
		output_fd = parser->output_fd;
	if (!(parser->command[1]))
		ft_putchar_fd('\n', output_fd);
	else
		echo_execute(parser, output_fd);
	return (1);
}

int	echo_valid_flag(char *str)
{
	int	i;

	i = 1;
	if (ft_strncmp(str, "-n", 2) != 0)
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	echo_execute(t_parser *parser, int output_fd)
{
	int	i;
	int	flag_nl;

	i = 1;
	flag_nl = 1;
	while (echo_valid_flag(parser->command[i]) == 1)
	{
		flag_nl = 0;
		i++;
	}
	while (parser->command[i])
	{
		ft_putstr_fd(parser->command[i++], output_fd);
		if (parser->command[i])
			ft_putchar_fd(' ', output_fd);
	}
	if (flag_nl != 0)
		ft_putchar_fd('\n', output_fd);
	return (1);
}
