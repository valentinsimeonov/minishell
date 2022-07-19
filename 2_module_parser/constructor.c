/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:13:02 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/19 16:02:46 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Sending Input in order to Construct: The ENV 2D Char Array, the Parser, The Command List, and Freeing the Parser */
int		constructor(t_data *data, char **line)
{
	char	*temp;
	t_list	*lexar_list;

	lexar_list = NULL;
	data->to_parser_list.paths = get_paths_array(*data->to_envp_data.envp_cp);
	data->to_parser_list.input_fd = STDIN_FILENO;
	data->to_parser_list.output_fd = STDOUT_FILENO;
	temp = ft_strtrim(*line, " \v\t\f\r\n");
	free(*line);
	*line = temp;
	if (!*line || !env_creator(data, line))
		return (parser_error_handling(data, &lexar_list, line, NULL));
	if(!parser(&lexar_list, *line))
		return (parser_error_handling(data, &lexar_list, line, NULL));
	if (!split_into_to_parser_lists(data, lexar_list))
		return (free_parser(data, &lexar_list, line, 1));
	// free_parser(data, &lexar_list, line, 0);
	// printf("In constructor:");
	// printf("%s\n", data->to_parser_list.commands);
	return (1);
}

/* Placing the Bash Variable PATH from the ENV into a 2D Char Array */
char	**get_paths_array(t_list *envp)
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

/* Detecting and Handling Errors in the Parser */
int		parser_error_handling(t_data *data, t_list **lexar_list, char **line, char *err)
{
	free_parser(data, lexar_list, line, 1);
	if (err)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	return (0);
}

/* Cleans the Command List */
int		free_parser(t_data *data, t_list **lexar_list, char **line, int clean_all)
{
	if (*line)
		free(*line);
	ft_lstclear(lexar_list, free);
	if (clean_all)
	{
		ft_lstclear(data->to_parser_list.commands, (void (*)(void *))free_array);
		free_array(data->to_parser_list.paths);
		data->to_parser_list.paths = NULL;
	}
	return (0);
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