/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/30 14:14:47 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	cwd[256];
	char	*line;
	char	**args;
	t_list	lexar_list;
	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
	(void)argc;
	(void)argv;
	(void)envp;
	while (7)
	{
		line = readline(cwd);
		//typing enter without args should just prompt cwd
		//needs to be fixed: input can also contain '  \n' etc
		if (line == "\n")
			continue ;
		args = ft_split(line, ' ');
		
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
