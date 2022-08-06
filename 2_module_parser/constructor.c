

#include "parser.h"

/* Cleans the Command List, If All Clean then Cleans Commands as well */
// static int	free_parser(t_list **lexar_list, char **line)
static int	free_parser(t_data *data, t_list **lexar_list, char **line,
	int clean_all)
{
	if (*line)
		free(*line);
	ft_lstclear(lexar_list, free);
	if (clean_all)
	{
		ft_lstclear(data->to_parser_list.sections, (void (*)(void *))free_array);
		free_array(data->to_parser_list.paths);
		data->to_parser_list.paths = NULL;
	}
	return (0);
}

/* Detecting and Handling Errors in the Parser */
static int	parser_error(t_data *data, t_list **lexar_list, char **line,
	char *err)
{
	free_parser(data, lexar_list, line, 1);
	if (err)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	return (0);
}

/* Placing the Bash Variable PATH from the ENV into a 2D Char Array */
static char	**get_paths_array(t_env **to_env_list)
{
	char	*path;
	char	**paths;

	path = get_env_value(to_env_list, "PATH");
	if (!path)
		return (NULL);
	else if (!ft_strlen(path))
	{
		if (path)
		{
			path = NULL;
			free(path);
		}
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (path)
	{
		path = NULL;
		free(path);
	} //// Problematic Freeing Here
	return (paths);
}

/* Sending Input in order to Construct: The ENV 2D Char Array, /
the Parser, The Command List, and Freeing the Parser */
int	parser(t_data *data, char **line)
{
	char	*tmp;
	t_list	*lexar_list;

	lexar_list = NULL;
	data->to_parser_list.paths = get_paths_array(&data->to_env_list);
	tmp = ft_strtrim(*line, " \v\t\f\r\n");
	free(*line);
	*line = tmp;
	if (!*line || !env_resolver(data, line))
		return (parser_error(data, &lexar_list, line, NULL));
	if (!lexer(*line, &lexar_list))
		return (parser_error(data, &lexar_list, line, NULL));
	if (!split_into_commands(data, &lexar_list))
		return (free_parser(data, &lexar_list, line, 1));
	//printf("Constructor = In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
	// if (*line)
	// 	free(*line);
	if (lexar_list)
		ft_lstclear(&lexar_list, free); //// After it Leaves the Parser it "error for object 0x100205290: pointer being freed was not allocated" in the Executor

	// if (lexar_list)
	// free_parser(data, &lexar_list, line, 0);

	// free(lexar_list);

	// if (*line)
	// 	free(*line);

	//printf("Constructor after Free = In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
	return (1);
}

/* Free 2D Char Array */
void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
