/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/05 13:58:55 by smischni         ###   ########.fr       */
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
	(void)argc; //Saskia: what's happening here?
	(void)argv;
	(void)envp;
	while (7) //Saskia: Why while(7)?
	{
		line = readline(cwd); //Saskia: shouldn't we display a prompt beforehand?
		//typing enter without args should just prompt cwd
		//needs to be fixed: input can also contain '  \n' etc
		if (line == "\n")
			continue ;
		//Saskia: line has to be saved for the history, incl. index --> array, maybe write it to a history file before terminating the shell
		args = ft_split(line, ' '); //Saskia: First splitting by '' or by ""? Also, maybe out this in a separate parsing function?
		//Saskia: here it should call a function to carry out the commands, so the executer, right?
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
