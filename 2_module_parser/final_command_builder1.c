/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_command_builder1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:51:34 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 15:08:44 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_pipes_in_lexar(t_list *lexar)
{
	t_list	*head;
	int		pipe_counter;

	head = lexar;
	pipe_counter = 1;
	while (head)
	{
		if (!ft_strncmp(head->line, "|", 2))
			pipe_counter++;
		head = head->next;
	}
	if (head)
		null_making(head);
	if (head)
		ft_lstclear(&head, free);
	if (head)
		free(head);
	return (pipe_counter);
}

/* Splits the Lexar List into Command List for executor */
int	split_into_commands(t_data *data, t_list *lexar)
{
	int		i;
	int		pipe_counter;
	t_list	*head;

	i = 0;
	head = lexar;
	pipe_counter = count_pipes_in_lexar(head);
	data->par.sections = ft_calloc(pipe_counter + 1, \
	sizeof(t_list *));
	while (lexar)
	{
		if (is_str_redir(lexar->line))
			ft_laddb(&data->par.sections[i], ft_ln(lexar->line));
		else if (!ft_strncmp(lexar->line, "|", 2))
		{
			ft_laddb(&data->par.pipe, ft_ln(lexar->line));
			i++;
		}
		else if (!is_str_redir(lexar->line))
			ft_laddb(&data->par.sections[i], ft_ln(lexar->line));
		lexar = lexar->next;
	}
	if (data->par.pipe)
		ft_lstclear(&data->par.pipe, free);
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
