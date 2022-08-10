/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:30:44 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 17:19:25 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_data		*data;

	(void)argc;
	(void)argv;
	data = initialiser(envp);
	data->to_env_list = create_env_list(envp);
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		data->lexar = NULL;
		data->line = readline("minishell:> ");
		if (data->line == NULL)
			break ;
		add_history(data->line);
		if (parser(data, &data->line))
			executor(data);
		if (data->line)
			free(data->line);
	}
	if (data->to_env_list)
		ft_lstclear_env(&data->to_env_list, free);
	exit(g_exit_status);
}

/* Initialises All Data */
t_data	*initialiser(char **envp)
{
	t_data	*data;

	(void)envp;
	data = ft_calloc(1, sizeof(t_data));
	return (data);
}
