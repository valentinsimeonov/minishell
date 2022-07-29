/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_command_builder1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 17:22:06 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/29 14:46:12 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// /*  Error handler */
// static int	error(char *err, char **command)
// {
// 	free_array(command);
// 	if (err)
// 		ft_putendl_fd(err, 2);
// 	else
// 		perror(err);
// 	return (0);
// }

// /* Adds one a String to Back of 2D Char Array */
// static int	array_addback(char ***array, char *str)
// {
// 	char	**tmp;

// 	if (!*array)
// 	{
// 		*array = ft_calloc(2, sizeof(char *));
// 		if (!*array)
// 			return (0);
// 		(*array)[0] = ft_strdup(str);
// 		if (!(*array)[0])
// 			return (0);
// 	}
// 	else
// 	{
// 		tmp = ft_calloc(char_array_len(*array) + 2, sizeof(char *));
// 		if (!tmp)
// 			return (0);
// 		ft_memmove(tmp, *array, char_array_len(*array) * sizeof(char *));
// 		tmp[char_array_len(*array)] = ft_strdup(str);
// 		if (!tmp[char_array_len(*array)])
// 			return (0);
// 		// free(*array);
// 		*array = tmp;
// 	}
// 	return (1);
// }


// int	count_pipes_in_lexar_list(t_list *lexar_list)
// {
// 	t_list	*head;
// 	int		pipe_counter;

// 	while (head)
// 	{
// 		if (!ft_strncmp(head->line, "|", 2))
// 			pipe_counter++;
// 		head = head->next;
// 	}
// 	return (pipe_counter);
// }


/* Splits the Lexar List into Command List for executor */
int	split_into_commands(t_data *data, t_list *lexar_list)
{
	int i = 0;
	int		pipe_counter = 1;
	t_list	*head;

	head = lexar_list;
	while (head)
	{
		if (!ft_strncmp(head->line, "|", 2))
			pipe_counter++;
		head = head->next;
	}
	data->to_parser_list.sections = ft_calloc(pipe_counter + 1, sizeof(t_list *));

	while (lexar_list)
	{
		if (is_str_redir(lexar_list->line))
			ft_lstadd_back(&data->to_parser_list.sections[i], ft_lstnew(lexar_list->line));
		else if (!ft_strncmp(lexar_list->line, "|", 2))
			i++;
		else if (!is_str_redir(lexar_list->line))
		{
			ft_lstadd_back(&data->to_parser_list.sections[i], ft_lstnew(lexar_list->line));
		}
		lexar_list = lexar_list->next;
	}
	//printf("Final Command Builder = In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
	// t_list	*head1;
	// head1 = data->to_parser_list.sections[0];
	// while (head1)
	// {
	// 	printf("In Command List at Sections Index 0: %s\n", ((char*)((t_list*)(head1->line))));
	// 	head1 = head1->next;
	// }
	// head1 = data->to_parser_list.sections[1]; 

	// while (head1)
	// 	{
	// 		printf("In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[1]->line)));
	// 		head1 = head1->next;
	// 	}

	// printf("Simple Print: %s\n", (char *)data->to_parser_list.sections[0]);
	// printf("Simple Print: %p\n", (void *)data->to_parser_list.sections[0]);
	
	// printf("In Command, Index 0: %s\n", command[0]);
	// printf("In Command, Index 1: %s\n", command[1]);
	// printf("%s\n", command[2]);
	// printf("%s\n", command[3]);
	// printf("In the Command Splitter");
	// print_list(&data->to_parser_list.sections[0]);
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


// //// * this Worked to Print the First Element in the 2D Array */

// /* Splits the Lexar List into Command List for executor */                         
// int	split_into_commands(t_data *data, t_list *lexar_list)
// {
// 	int i =0;
// 	char	*command;

// 	command = NULL;
// 	while (lexar_list)
// 	{
// 		if (is_str_redir(lexar_list->line))
// 		{
// 			array_addback(&command, lexar_list->line);
// 		}
// 		else if (!ft_strncmp(lexar_list->line, "|", 2))
// 		{
// 			// puts("pipe error");
// 			if (!command || !lexar_list->next)
// 				return (error("syntax error near unexpected token `|'",
// 						command));
// 			ft_lstadd_back(data->to_parser_list.sections, ft_lstnew(*command));
// 			command = NULL;
// 		}
// 		else if (!array_addback(&command, lexar_list->line))
// 			return (error(NULL, command));
// 		// puts("hi");
		
// 		else if (command)
// 		{
// 			ft_lstadd_back(data->to_parser_list.sections, ft_lstnew(*command));
// 			printf("Last If Condition in While: %p\n", (void *)data->to_parser_list.sections[i++]);

// 		}
// 		if (command)
// 		{
// 			printf("In While00: %s\n", command[0]);
// 			printf("In While01: %s\n", command[1]);
// 		}
// 		lexar_list = lexar_list->next;
// 	}
// 	printf("In Command List at Sections Index 0: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[0]->line)));
// 	// printf("Pointer index 1: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[1]->line)));

// 	printf("In Command List at Sections Index 1: %s\n", ((char*)((t_list*)((t_parser)(data->to_parser_list)).sections[1]->line)));
// 	printf("Simple Print: %s\n", (char *)data->to_parser_list.sections[0]);
// 	printf("Simple Print: %p\n", (void *)data->to_parser_list.sections[0]);
	
// 	// printf("In Command, Index 0: %s\n", command[0]);
// 	// printf("In Command, Index 1: %s\n", command[1]);
// 	// printf("%s\n", command[2]);
// 	// printf("%s\n", command[3]);

// 		// printf("In the Command Splitter");
// 		// print_list(data->to_parser_list.sections);
// 	return (1);
// }

