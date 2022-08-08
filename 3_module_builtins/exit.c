/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 15:16:23 by smischni          #+#    #+#             */
/*   Updated: 2022/08/07 21:10:47 by vsimeono         ###   ########.fr       */
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
	if (env)
		ft_lstclear_env(&env, free);
	if (parser->sections)
		ft_lstclear(parser->sections, (void (*)(void *))free_array);  ////Working last night
	// free(env->bash_variable);///PLATZHALTER -> UNUSED PARAMETER
	// free(data);
	exit(EXIT_SUCCESS);
	return (1);
}
