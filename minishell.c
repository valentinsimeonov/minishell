/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/19 15:31:13 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char	*line;
	t_list	*lexar_list;
	t_data	*data;
	// t_parser *parser;

	lexar_list = NULL;
	data = env_builder(envp);
	(void)argc;
	(void)argv;
	// (void)envp;
	
	// /* Creating the ENV List */
	// create_env_list(envp);

	/* Creating the LEXAR */
	int		i;
	i = 0;
	while (i < 3)
	{
		line = readline("minishell:> ");
		if (line == NULL)
			break ;
		add_history(line);
		constructor(data, &line);
		printf("First Line\n");
		print_list(&lexar_list);
		// printf("%s", parser.commands);
		// printf("%p", data->to_parser_list.commands.line);
		i++;
	}
	// printf("%s", data->to_parser_list.commands[1]->line);
	// print_list(&lexar_list); 
	return (0);
}
