

#include "builtins.h"

int	ft_exit(t_data *data, int flag_pipe)
{
	t_parser	*parser;
	t_env		*env;

	parser = &data->to_parser_list;
	env = &data->to_env_list;
	if (flag_pipe == 1)
		return (1);
	free_str_array(parser->command);
	free_str_array(parser->paths);
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
