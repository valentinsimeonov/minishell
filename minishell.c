

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	//t_env 		*env_list;
	
	// t_list	*lexar_list;
	t_data		*data;
	// t_parser	*test;
	// lexar_list = NULL;
	/* Creating the ENV List */
	data = env_builder(envp);
	data->to_env_list = *create_env_list(envp);
	//print_env_list(&env_list);
	(void)argc;
	(void)argv;

	//* Checking for Signals **/
	signal_check(data);

	

	int		i;
	i = 0;
	while (i < 10)
	{
		ft_putstr_fd("Neuer Durchlauf:\n", 2);
		line = readline("minishell:> ");
		if (line == NULL)
			break ;
		add_history(line);
		parser(data, &line);

		//printf("Main = In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
		//printf("Main = In Command List at Sections Index 1: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[1]->line)));

		//print_all_input(data);
		executor(data);
		// print_all_input(data);
		// printf("%s", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));


		// printf("%s", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections->line[1])));

		
		// void *pline = ((t_list**)((t_parser)(data->to_parser_list)).sections[0]->line);
		// printf("%p \t%s \n", pline, (char *)pline);

		// printf("%s", ((char*)((data->to_parser_list)).sections[0]->line));

		
		// printf("%s\n", data->to_parser_list);
		// printf("%p\n", data->to_parser_list);
		// print_list_test(data);
		i++;
	}
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
	i = 0;
	while (parser->command[i])
	 	printf("%s\n", parser->command[i++]);
	return (1);
}
