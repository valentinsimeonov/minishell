/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:16:23 by smischni          #+#    #+#             */
/*   Updated: 2022/08/06 17:47:52 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(t_env *env, t_parser *parser, int flag_pipe)
{
	if (flag_pipe == 1)
		return (1);
	free_str_array(parser->command);
	free_lst_array(parser->sections);
	close(parser->input_fd);
	close(parser->output_fd);
	close(parser->store_stdin);
	close(parser->store_stdout);
	//parser itself?
	//free env list
	free(env->bash_variable);///PLATZHALTER -> UNUSED PARAMETER
	exit(EXIT_SUCCESS);
	return (1);
}
