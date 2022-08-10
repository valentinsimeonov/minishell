/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:09:58 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 17:56:22 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static int	get_clean_input(char *line, t_list **lexar_list,
	int *start, int *end)
{
	char	*content;

	content = ft_substr(line, *start, *end - *start);
	if (!content || !clean_quote(&content))
		return (0);
	ft_laddb(lexar_list, ft_ln(content));
	while (line[*end] && ft_isspace(line[*end]))
		(*end)++;
	*start = *end;
	return (1);
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
int	lexer(char *line, t_list **lexar_list)
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
			if (!get_clean_input(line, lexar_list, &start, &end))
				return (0);
		}
	}
	if (line[start] && !get_clean_input(line, lexar_list, &start, &end))
		return (0);
	return (1);
}
