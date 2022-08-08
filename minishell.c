

#include "minishell.h"

int global_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		*data;
	// t_list		*lexar_list;
	// lexar_list = NULL;

	/* Creating the ENV List */
	data = env_builder(envp);
	data->to_env_list = create_env_list(envp); /// Variable is Here Just for Testing Purposes

	(void)argc;
	(void)argv;

	/* Checking for Signals */
	signal(SIGINT, signal_handler_parent);
	signal(SIGQUIT, SIG_IGN);

	int		i;
	i = 0;
	while (i < 10)
	{
		line = readline("minishell:> ");
		if (line == NULL)
			break ;
		add_history(line);
		parser(data, &line);
		// print_all_input(data);
		//printf("End of Parser, Start of Executor\n");
		executor(data);

		// if (lexar_list)
		// 	ft_lstclear(&lexar_list, free); //// After it Leaves the Parser it "error for object 0x100205290: pointer being freed was not allocated" in the Executor

		// if (data->to_parser_list.sections)
		// 	ft_lstclear(data->to_parser_list.sections, (void (*)(void *))free_array);  ////Working last night

		// free_lst_array(data->to_parser_list.sections);
		// // data->to_parser_list = NULL;  //// Added in the Morning
		// if (data->to_parser_list.paths)

		// 	free_array(data->to_parser_list.paths); ////Working last night

		// if (lexar_list)
		// 	free(lexar_list);
		if (line)
			free(line);  ///// Most Definitely HERE
		i++;
	}
	if (data->to_env_list)
		ft_lstclear_env(&data->to_env_list, free);
	free(data);
	return (0);
}

/* Initialises All Data */
t_data	*env_builder(char **envp)
{
	t_data	*data;
	(void)envp;
	data = ft_calloc(1, sizeof(t_data));
	// data->to_parser_list.sections = ft_calloc(1, sizeof(t_list *));  //// ///// Most Definitely Not Needed
	return (data);
}

//temporary function to check input
int	print_all_input(t_data *data)
{
	//t_env		*env;
	t_parser	*parser;
	t_list		*cur_sec;
	int			i;
	int			j;

	i = 0;
	/*env = (data->to_env_list);
	printf("\nCHECK T_DATA CONTENT:\n");
	printf("\nENV:\n");
	while (env)
	{
		printf("%s=%s\n", env->bash_variable, env->bash_v_content);
		env = env->next;
	}*/
	parser = &(data->to_parser_list);
	printf("\nSECTIONS:\n");
	while (parser->sections[i])
	{
		cur_sec = parser->sections[i];
		j = 1;
		while (cur_sec)
		{
			printf("%d. list element: %s\n", j++, (char *)cur_sec->line);
			cur_sec = cur_sec->next;
		}
		i++;
	}
	/*printf("\nPATH:\n");
	i = 0;
	while (parser->paths[i])
		printf("%s\n", parser->paths[i++]);*/
	printf("\nCOMMANDS:\n");
	i = 0;
	while (parser->command[i])
	  	printf("%s\n", parser->command[i++]);
	return (1);
}
