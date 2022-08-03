/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:29:14 by smischni          #+#    #+#             */
/*   Updated: 2022/08/03 18:12:05 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(t_parser *parser)
{
	int	i;
	int	flag_nl;

	i = 1;
	flag_nl = 1;
	if (!(parser->command[i]))
		ft_putchar_fd('\n', parser->output_fd);
	else
	{
		while (echo_valid_flag(parser->command[i]) == 1)
		{
			flag_nl = 0;
			i++;
		}
		while (parser->command[i])
		{
			ft_putstr_fd(parser->command[i++], parser->output_fd);
			ft_putchar_fd(' ', parser->output_fd);
		}
		if (flag_nl != 0)
			ft_putchar_fd('\n', parser->output_fd);
	}
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
