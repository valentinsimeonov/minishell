/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:21 by smischni          #+#    #+#             */
/*   Updated: 2022/07/21 18:05:47 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	create_command_array(int count, t_parser *parser, t_list *sec)
{
	int	i;

	i = 0;
	parser->command = ft_calloc(count + 1, sizeof(char *));//remember to free after execution
	if (!parser->command)
		return (0);//error handling TBD
	while (sec)
	{
		if ((is_infile(sec->line) || is_outfile(sec->line)) && sec->next)
			sec = sec->next;
		else
			parser->command[i] = sec->line;
		sec = sec->next;
	}
	//OPEN: ADD PATH TO FIRST ARRAY ELEMENT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! + ERROR IF NO PATH
	return (1);
}
