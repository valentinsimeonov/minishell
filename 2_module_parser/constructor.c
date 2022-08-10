/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:41:51 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 15:14:31 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Cleans the Command List, If All Clean then Cleans Commands as well */
// static int	free_parser(t_list **lexar, char **line)
static int	free_parser(t_data *data, t_list **lexar, char **line,
	int clean_all)
{
	if (*line)
		free(*line);
	ft_lstclear(lexar, free);
	if (clean_all)
	{
		ft_lstclear(data->par.sections, \
		(void (*)(void *))free_array);
		free_array(data->par.paths);
		data->par.paths = NULL;
	}
	return (0);
}

/* Detecting and Handling Errors in the Parser */
static int	parser_error(t_data *data, t_list **lexar, char **line,
	char *err)
{
	free_parser(data, lexar, line, 1);
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
			path = NULL;
		return (NULL);
	}
	paths = ft_split(path, ':');
	if (path)
		path = NULL;
	return (paths);
}

/* Sending Input in order to Construct: The ENV 2D Char Array, /
the Parser, The Command List, and Freeing the Parser */
int	parser(t_data *data, char **line)
{
	char	*tmp;

	data->par.paths = get_paths_array(&data->to_env_list);
	tmp = ft_strtrim(*line, " \v\t\f\r\n");
	free(*line);
	*line = tmp;
	if (!*line || !env_resolver(data, line))
		return (parser_error(data, &data->lexar, line, NULL));
	if (!lexer(*line, &data->lexar))
		return (parser_error(data, &data->lexar, line, NULL));
	if (!split_into_commands(data, data->lexar))
		return (free_parser(data, &data->lexar, line, 1));
	if (data->lexar)
		null_making(data->lexar);
	if (data->lexar)
		ft_lstclear(&data->lexar, free);
	if (data->lexar)
		free(data->lexar);
	return (1);
}

void	null_making(t_list *lexar)
{
	while (lexar)
	{
		lexar->line = NULL;
		lexar = lexar->next;
	}
}
