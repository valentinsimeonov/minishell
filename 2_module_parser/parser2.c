/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:35:19 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 15:14:19 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Removes char at Index and Removes the New Allocated String */
char	*str_remove_char_at1(char *str, int idx)
{
	char	*new_str;
	char	*start;

	if (!str || idx < 0)
		return (NULL);
	if (idx >= (int)ft_strlen(str))
		return (str);
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*str)
	{
		if (idx == 0)
		{
			str++;
			if (!*str)
				break ;
		}
		*new_str = *str;
		str++;
		new_str++;
		idx--;
	}
	return (start);
}

/* Check if the char is a type of Invisible Char */
int	ft_isspace(int c)
{
	if (c == '\v' || c == '\f' || c == '\r'
		|| c == '\t' || c == '\n' || c == ' ')
		return (1);
	return (0);
}

// Only those that we need to interpret in project
int	is_meta_char(int c)
{
	if (c == '>' || c == '<' || c == '|' || c == '$')
		return (1);
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
