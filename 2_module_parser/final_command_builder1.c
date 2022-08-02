/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_command_builder1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:22:06 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/01 18:16:20 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_pipes_in_lexar_list(t_list *lexar_list)
{
	t_list	*head;
	int		pipe_counter;

	head = lexar_list;
	pipe_counter = 1;
	while (head)
	{
		if (!ft_strncmp(head->line, "|", 2))
			pipe_counter++;
		head = head->next;
	}
	return (pipe_counter);
}

/* Splits the Lexar List into Command List for executor */
int	split_into_commands(t_data *data, t_list *lexar_list)
{
	int		i;
	int		pipe_counter;
	t_list	*head;

	i = 0;
	head = lexar_list;
	pipe_counter = count_pipes_in_lexar_list(head);
	data->to_parser_list.sections = ft_calloc(pipe_counter + 1, \
	sizeof(t_list *));
	while (lexar_list)
	{
		if (is_str_redir(lexar_list->line))
			ft_lstadd_back(&data->to_parser_list.sections[i], \
			ft_lstnew(lexar_list->line));
		else if (!ft_strncmp(lexar_list->line, "|", 2))
			i++;
		else if (!is_str_redir(lexar_list->line))
		{
			ft_lstadd_back(&data->to_parser_list.sections[i], \
			ft_lstnew(lexar_list->line));
		}
		lexar_list = lexar_list->next;
	}
	printf("Final Command Builder = In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
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
