/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/29 16:28:55 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char	*line;
	char	space;
	t_list	lexar_list;
	

	(void)argc;
	(void)argv;
	(void)envp;
	space = ' ';
	while (7)
	{
		line = readline("minishell> ");
		create_lexar(&lexar_list, ft_split(line, space));
	}
	return (0);
}

void	create_lexar(t_list *lexar_list, char **array)
{
	int		i;

	i = 0;
	while (i < size_of_array(array))
	{
		ft_lstadd_back(&lexar_list, create_stack_value(array));
		i++;
	}
}

int		size_of_array(char **array)
{
	int		lenght;

	lenght = sizeof(array) / sizeof(array);
	return(lenght);
}

t_list	*create_stack_value(char **value)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->line = *value;
	element->next = NULL;
	return (element);
}

// char x[10];
// int elements_in_x = sizeof(x) / sizeof(x[0]);
// char	**ft_split(char const *s, char c)