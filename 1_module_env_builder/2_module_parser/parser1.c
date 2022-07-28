/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:04:53 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/26 19:48:16 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


#include "parser.h"

/*	Removing the Quotes */
static int	clean_quote(char **str)
{
	int		i;
	char	quote;
	char	*tmp;

	quote = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((!quote && ((*str)[i] == '"' || (*str)[i] == '\''))
			|| (quote && (*str)[i] == quote))
		{
			if (!quote && ((*str)[i] == '"' || (*str)[i] == '\''))
				quote = (*str)[i];
			else if (quote && (*str)[i] == quote)
				quote = 0;
			tmp = str_remove_char_at1(*str, i);
			free(*str);
			if (!tmp)
				return (0);
			*str = tmp;
		}
		else
			i++;
	}
	return (1);
}

/*	Dividing in to Substrings and Sending the Substrings
    to have the Quotes Removed, Creating the List */
static int	get_clean_input(char *line, t_list **clean_input_list,
	int *start, int *end)
{
	char	*content;

	content = ft_substr(line, *start, *end - *start);
	if (!content || !clean_quote(&content))
		return (0);
	ft_lstadd_back(clean_input_list, ft_lstnew(content));
	while (line[*end] && ft_isspace(line[*end]))
		(*end)++;
	*start = *end;
	// print_list(clean_input_list);
	return (1);
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
			printf("%s\n", (char *)temp_p->line);
			temp_p = temp_p->next;
		}
		printf("%s", "In List: ");
		printf("%s\n", temp_p->line);
	}
}

/*	Checking if in Line there is a In File Char or Here Doc Char	*/
static void	get_metachar_end(char *line, int *end)
{
	if ((line[*end] == '>' && line[*end + 1] == '>')
		|| (line[*end] == '<' && line[*end + 1] == '<'))
		*end += 2;
	else
		*end += 1;
}

/*	Finding the Last Quote	*/
static void	get_quote_end(char *line, int *end)
{
	char	quote;

	quote = line[*end];
	(*end)++;
	while (line[*end] && quote != line[*end])
		(*end)++;
	if (line[*end])
		(*end)++;
}

/*	Checking for Quotes, Sending the Line
    to the List Creating Function  */
int	lexer(char *line, t_list **clean_input)
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
			get_quote_end(line, &end);
		else if (is_meta_char(line[end]))
			get_metachar_end(line, &end);
		else
			end++;
		if (line[start] && (ft_isspace(line[end]) || is_meta_char(line[end])
				|| is_meta_char(line[end - 1])))
		{
			if (!get_clean_input(line, clean_input, &start, &end))
				return (0);
		}
	}
	if (line[start] && !get_clean_input(line, clean_input, &start, &end))
		return (0);
	print_list(clean_input);
	return (1);
}
