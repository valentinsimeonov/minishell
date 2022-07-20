/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/20 13:08:41 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*lexar_list;
	t_data	*data;

	lexar_list = NULL;
	/* Creating the ENV List */
	data = env_builder(envp);
	create_env_list(envp);
	(void)argc;
	(void)argv;

	//* Checking for Signals **/
	signal_check(data);
	
	// /* Creating the ENV List */
	// create_env_list(envp);

	int		i;
	i = 0;
	while (i < 3)
	{
		line = readline("minishell:> ");
		if (line == NULL)
			break ;
		add_history(line);
		constructor(data, &line);
		i++;
	}
	return (0);
}
