/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/31 22:13:55 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char	*line;
	t_list	*lexar_list;
	t_env	*env_list;

	
	lexar_list = NULL;
	env_list = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
 /// FOR ENVP /////
	// int		i;
	// int		j;
	// i = 0;
	// j = 0;
	// while(i < 3)
	// {
	// 	printf("%c", envp[i][j]);
	// 	i++;
	// }
	// printf("%s", *envp);
	// env_list = create_env_list(envp);

	int		i;
	i = 0;
	while (i < 3)
	{
		line = readline("minishell> ");
		create_lexar(lexar_list, line);
		// create_env_list(envp);
		i++;
	}
	return (0);
}


			/*             LEXAR				*/

/* Creating the Lexar Linked List with the Arguments from the Prompt */
void	create_lexar(t_list *lexar_list, char *line)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_split(line, ' ');
	if (ft_strchr(line, '"'))
	{
		array = ft_split(line, '"');
	}
	else if (ft_strchr(line, '\''))
	{
		array = ft_split(line, '\'');
	}
	while (i < size_of_array(array))
	{
		ft_lstadd_back(&lexar_list, create_element(&array[i]));
		i++;
	}
	print_list(&lexar_list);
}

/* Getting the Length of a 2D Array */
int		size_of_array(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return(i);
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


			/*				ENV List			*/

// t_env		create_env_list(char	**envp)
// {
// 	t_env	*env;

// 	env = NULL;
// 	// char	*line; 
// 	printf("%s", *envp);
// 	return (*env);
// }
			/*				PARSER				*/
// Pseudo Code:
// if (ft_strchr(lexar_list[i], '|'))
// 	array = ft_split(lexar_list[i], '|');
// 	ft_lstadd_back(&command_list, create_element(&array[i]));

// void	create_command_list(t_list *lexar_list)
// {
// 	int		i;
// 	char	**array;
// 	char	*char_location;

// 	i = 0;
// 	while (lexar_list->next != NULL)
// 	{
// 		if (ft_strchr(lexar_list->line, '|'))
// 		{
// 			char_location = ft_strchr(lexar_list->line, '|');
// 			array = ft_split(lexar_list->line, '|');
// 			while (i < size_of_array(array)
// 			{
// 				ft_lstadd_back(&command_list, create_element(&array[i]));
// 				i++;
// 			}
// 			print_list(&lexar_list);
// 		}
// 	}
// }

//  /////SEcond Try for PArser ///
 

// Pseude code:

// while (lexar_list->next != NULL)
// 	{
// 		if (!ft_strchr(lexar_list->line, '|'))
			
			

 
// void	create_command_list(t_list *lexar_list)
// {
// 	int		i;
// 	int		j;
// 	char	**array;
// 	char	*char_location;

// 	i = 0;
// 	while (lexar_list->next != NULL)
// 	{
// 		if (ft_strchr(lexar_list->line, '|'))
// 		{
// 			// char_location = ft_strchr(lexar_list->line, '|');
// 			array = ft_split(lexar_list->line, '|');
// 			while (array[i] != NULL )
// 			{
// 				if (!strchr(array[j], '|'))
// 				{
// 					while (!strchr(array[j], '|'))
// 					{
// 						ft_lstadd_back(&parser_list, create_element(&array[j]));
// 						j++;
// 					}
// 				}
// 				else if (strchr(array[k], '|'))
// 				{
// 					ft_lstadd_back(&parser_list, create_element(&array[k]));
// 				}
// 				i++;
// 			}
// 		}
// 		next = lexar_list->next;
// 	}

// }

			
// 			while (*arrayi < size_of_array(array))
// 			{
// 				ft_lstadd_back(&command_list, create_element(&array[i]));
// 				i++;
// 			}
// 			print_list(&lexar_list);
// 		}
// 	}
// }









	



///////////  Linked Lists Functions   /////////////




/* Getting the Lenght of the Linked List */
int	len_list(t_list **list)
{
	t_list	*temp;
	int		counter;

	temp = *list;
	counter = 0;
	if (*list != NULL)
	{
		counter = 1;
		while (temp->next != NULL)
		{
			temp = temp->next;
			counter++;
		}
	}
	return (counter);
}

/* Function to delete the entire linked list */
void	delete_list(t_list **list)
{
   /* deref **list to get the real head */
   t_list	*head;
   t_list	*next;
   
   head = *list;
   while (head != NULL) 
   {
       next = head->next;
       free(head);
       head = next;
   }
   /* deref **list to affect the real head back
      in the caller. */
   *list = NULL;
}