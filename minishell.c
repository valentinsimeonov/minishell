

#include "minishell.h"

int global_exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_data		*data;

	/* Creating the ENV List */
	data = env_builder(envp);   
	// data = main_data_initialiser(envp);
	data->to_env_list = *create_env_list(envp); /// Variable is Here Just for Testing Purposes

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
		executor(data);
		/*if (data->to_parser_list.sections)
			ft_lstclear(data->to_parser_list.sections, (void (*)(void *))free_array);
		if (data->to_parser_list.paths)
			free_array(data->to_parser_list.paths);*/
		// free_minishell(data);
		// print_list_test(data);
		i++;
	}
	free_minishell(data);
	return (0);
}


//temporary function to check input
int	print_all_input(t_data *data)
{
	t_env		*env;
	t_parser	*parser;
	t_list		*cur_sec;
	int			i;
	int			j;
	
	i = 0;
	env = &(data->to_env_list);
	printf("\nCHECK T_DATA CONTENT:\n");
	printf("\nENV:\n");
	while (env)
	{
		printf("%s=%s\n", env->bash_variable, env->bash_v_content);
		env = env->next;
	}
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
	printf("\nPATH:\n");
	i = 0;
	while (parser->paths[i])
		printf("%s\n", parser->paths[i++]);
	printf("\nCOMMANDS:\n");
	// i = 0;
	// while (parser->command[i])
	//  	printf("%s\n", parser->command[i++]);
	return (1);
}
