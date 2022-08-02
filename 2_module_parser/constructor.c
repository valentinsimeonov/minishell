

#include "parser.h"

/* Cleans the Command List, If All Clean then Cleans Commands as well */
static int	free_parser(t_list **lexar_list, char **line)
{
	if (*line)
		free(*line);
	ft_lstclear(lexar_list, free);
	return (0);
}

/* Detecting and Handling Errors in the Parser */
static int	parser_error(t_list **lexar_list, char **line,
	char *err)
{
	free_parser(lexar_list, line);
	if (err)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	return (0);
}

/* Placing the Bash Variable PATH from the ENV into a 2D Char Array */
static char	**get_paths_array(t_list *envp)
{
	char	*path;
	char	**paths;

	path = get_env_value(envp, "PATH");
	if (!path)
		return (NULL);
	else if (!ft_strlen(path))
	{
		free(path);
		return (NULL);
	}
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

/* Sending Input in order to Construct: The ENV 2D Char Array, /
the Parser, The Command List, and Freeing the Parser */
int	parser(t_data *data, char **line)
{
	char	*tmp;
	t_list	*lexar_list;

	lexar_list = NULL;
	data->to_parser_list.paths = get_paths_array(*data->to_envp_data.envp_cp);
	tmp = ft_strtrim(*line, " \v\t\f\r\n");
	free(*line);
	*line = tmp;
	if (!*line || !env_resolver(data, line))
		return (parser_error(&lexar_list, line, NULL));
	if (!lexer(*line, &lexar_list))
		return (parser_error(&lexar_list, line, NULL));
	if (!split_into_commands(data, lexar_list))
		return (free_parser(&lexar_list, line));
	//printf("Constructor = In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
	// ft_lstclear(&lexar_list, free);
	// free_parser(data, &lexar_list, line, 0);
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
