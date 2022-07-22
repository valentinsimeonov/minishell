/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/23 00:59:26 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	// t_list	*lexar_list;
	t_data		*data;
	// t_parser	*test;
	// lexar_list = NULL;
	/* Creating the ENV List */
	data = env_builder(envp);
	create_env_list(envp);
	(void)argc;
	(void)argv;

	//* Checking for Signals **/
	signal_check(data);

	int		i;
	i = 0;
	while (i < 3)
	{
		line = readline("minishell:> ");
		if (line == NULL)
			break ;
		add_history(line);
		parser(data, &line);
		// printf("%s", ((char*)((t_list*)((t_parser)(data->to_parser_list)).commands[0]->line)));
		// printf("%s", ((char*)((t_list*)((t_parser)(data->to_parser_list)).commands[1]->line)));

		// printf("%s\n", data->to_parser_list);
		// printf("%p\n", data->to_parser_list);
		// print_list_test(data);
		i++;
	}
	return (0);
}
