/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:04:53 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/19 09:29:58 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*		LEXAR/PARSER		*/

/*	Checking for Quotes, Sending the Line to the List Creating Function*/
int		parser(t_list **lexar_list, char *line)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (line[end])
	{
		if (line[end] == '#')
			ft_bzero(&line[end], ft_strlen(&line[end]));
		if (line[end] == '"' || line[end] == '\'')
			finding_last_quote(line, &end);
		else if (is_special_char(line[end]))
			is_file_sign(line, &end);
		else
			end++;
		if (line[start] && (is_invisible(line[end]) || is_special_char(line[end]) || is_special_char(line[end - 1])))
			if (!create_lexar_list(line, lexar_list, &start, &end))
				return (0);
	}
	if (line[start] && !create_lexar_list(line, lexar_list, &start, &end))
		return (0);
	// print_list(lexar_list);  /// TODO DELETE This
	return (1);
}

/*	Dividing in to Substrings and Sending the Substrings to have the Quotes Removed, Creating the List */
int	create_lexar_list(char *line, t_list **lexar_list, int *start, int *end)
{
	char	*content;
	
	content = ft_substr(line, *start, *end - *start);
	if (!content || !remove_quotes(&content))
		return (0);
	ft_lstadd_back(lexar_list, create_element(&content));
	while (line[*end] && is_invisible(line[*end]))
		(*end)++;
	*start = *end;
	return (78);
}

/* Check if the char is a type of Invisible Char */
int	is_invisible(int c)
{
	if (c == '\v' || c == '\f' || c == '\r' || c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

/*	Removing the Quotes */
int	remove_quotes(char **str)
{
	int		i;
	char	quote;
	char	*temp;
	
	quote = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((!quote && ((*str)[i] == '"' || (*str)[i] == '\'')) || (quote && (*str)[i] == quote))
		{
			if (!quote && ((*str)[i] == '"' || (*str)[i] == '\''))
				quote = (*str)[i];
			else if (quote && (*str)[i] == quote)
				quote = 0;
			temp = remove_char(*str, i);
			free(*str);
			if (!temp)
				return (0);
			*str = temp;
		}
		else i++;
	}
	return (1);
}

/*	Removing Character from a String Function */
char	*remove_char(char *str, int index)
{
	char	*new_str;
	char	*start;

	if (!str || index < 0)
		return (NULL);
	if (index >= (int)ft_strlen(str))
		return (str);
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*str)
	{
		if (index == 0)
		{
			str++;
			if (!*str)
				break;
		}
		*new_str = *str;
		str++;
		new_str++;
		index--;
	}
	return(start);
}

/* Creating One Element to Place in a Linked List */
t_list	*create_element(char **value)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->line = *value;
	element->next = NULL;
	return (element);
}

/*	Finding the Last Quote	*/
void	finding_last_quote(char *line, int *end)
{
	char	quote;

	quote = line[*end];
	(*end)++;
	while (line[*end] && quote != line[*end])
		(*end)++;
	if (line[*end])
		(*end)++;
}

/*	Checking if in Line there is a In File Char or Here Doc Char	*/
void	is_file_sign(char *line, int *end)
{
	if ((line[*end] == '>' && line[*end + 1] == '>') || (line[*end] == '<' && line[*end +  1] == '<'))
		*end += 2;
	else
		*end += 1;
}

/*	Checking if there is a $, |, In file or Outfile Character in the Line	*/
int		is_special_char(int c)
{
	if (c == '<' || c == '>' || c == '$' || c == '|')
		return (1);
	return (0);
}

/* Printing the Elements from a Linked List */
void	print_list(t_list **stack)
{
	t_list *temp_p;
	
	temp_p = *stack;
	if (*stack == NULL)
		printf("List is Empty\n");
	if (*stack != NULL)
	{	
		while (temp_p->next != NULL)
		{
			printf("%s", "In List: ");
			printf("%s\n", temp_p->line);
			temp_p = temp_p->next;
		}
		printf("%s", "In List: ");
		printf("%s\n", temp_p->line);
	}
}
