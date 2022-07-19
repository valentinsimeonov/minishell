/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_parser_list_splitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:22:06 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/18 15:48:11 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Handles Errors
int	error(char *err, char **to_parser_list)
{
	free_array(to_parser_list);
	if (err)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	return (0);
}

// Open heredoc pipe and write the heredoc string to it
int	get_heredoc(char *stop_str)
{
	int		heredoc_pipe[2];
	char	*line;

	if (pipe(heredoc_pipe) < 0)
		return (-1);
	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(line, stop_str, ft_strlen(stop_str) + 1))
			break ;
		write(heredoc_pipe[1], line, ft_strlen(line));
		write(heredoc_pipe[1], "\n", 1);
	}
	if (close(heredoc_pipe[1]) < 0)
		return (-1);
	return (heredoc_pipe[0]);
}

// Get input/ouput fd
// Return 0 if error otherwise 1
int	get_inout_fd(t_data *data, t_list **list, char **to_parser_list)
{
	char	*filename;

	if (!(*list)->next)
		return (error("syntax error near unexpected token `newline'",
				to_parser_list));
	filename = (*list)->next->line;
	if (!ft_strncmp((*list)->line, ">>", 3))
		data->to_parser_list.output_fd = open(filename,
				O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (!ft_strncmp((*list)->line, "<<", 3))
		data->to_parser_list.input_fd = get_heredoc(filename);
	else if (!ft_strncmp((*list)->line, ">", 2))
		data->to_parser_list.output_fd = open(filename,
				O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (!ft_strncmp((*list)->line, "<", 2))
		data->to_parser_list.input_fd = open(filename, O_RDONLY);
	if (data->to_parser_list.output_fd < 0 || data->to_parser_list.input_fd < 0)
	{
		perror(filename);
		free_array(to_parser_list);
		return (0);
	}
	*list = (*list)->next;
	return (1);
}

// Add one more string to back of 2d char array
// Return 0 if error otherwise 1
int	array_addback(char ***array, char *str)
{
	char	**tmp;

	if (!*array)
	{
		*array = ft_calloc(2, sizeof(char *));
		if (!*array)
			return (0);
		(*array)[0] = ft_strdup(str);
		if (!(*array)[0])
			return (0);
	}
	else
	{
		tmp = ft_calloc(char_array_len(*array) + 2, sizeof(char *));
		if (!tmp)
			return (0);
		ft_memmove(tmp, *array, char_array_len(*array) * sizeof(char *));
		tmp[char_array_len(*array)] = ft_strdup(str);
		if (!tmp[char_array_len(*array)])
			return (0);
		free(*array);
		*array = tmp;
	}
	return (1);
}

/* Split clean input into s_to_parser_list structure for executor */
int	split_into_to_parser_lists(t_data *data, t_list *lexar_list)
{
	char	**to_parser_list;

	to_parser_list = NULL;
	while (lexar_list)
	{
		if (is_str_redir(lexar_list->line))
		{
			if (!get_inout_fd(data, &lexar_list, to_parser_list))
				return (0);
		}
		else if (!ft_strncmp(lexar_list->line, "|", 2))
		{
			if (!to_parser_list || !lexar_list->next)
				return (error("syntax error near unexpected token `|'",
						to_parser_list));
			ft_lstadd_back(data->to_parser_list.commands, ft_lstnew(to_parser_list));
			to_parser_list = NULL;
		}
		else if (!array_addback(&to_parser_list, lexar_list->line))
			return (error(NULL, to_parser_list));
		lexar_list = lexar_list->next;
	}
	if (to_parser_list)
		ft_lstadd_back(data->to_parser_list.commands, ft_lstnew(to_parser_list));
	return (1);
}

/* Get Length of 2D Char Array */
int	char_array_len(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}


/* Return 1 if String is Redirected */
int	is_str_redir(char *str)
{
	if (!ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, ">>", 3)
		|| !ft_strncmp(str, "<", 2)
		|| !ft_strncmp(str, "<<", 3))
		return (1);
	return (0);
}
