/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/01 20:08:31 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char	*line;
	t_list	*lexar_list;

	lexar_list = NULL;
	(void)argc;
	(void)argv;
	// (void)envp;
	
	/* Creating the ENV List */
	create_env_list(envp);
	
	/* Creating the LEXAR */
	int		i;
	i = 0;
	while (i < 3)
	{
		line = readline("minishell> ");
		create_lexar(lexar_list, line);
		i++;
	}
	
	return (0);
}

/*				ENV List			*/

void		create_env_list(char	**envp)
{
	t_env	*env_list;
	char	**array;
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	env_list = NULL;
	while (envp[i] != NULL)
	{
		array = ft_split(envp[i], '=');
		// printf("%s", *array);
		j = 0;
		while(array[j] != NULL && j < 2)
		{
			ft_lstadd_back_env_element(&env_list, create_env_element(array));
			// printf("%s", env_list->bash_v_content);
			j++;
		}
		i++;
	}
	print_env_list(&env_list);
}

/* Creating One Element with Two Variables to Place in a Linked List */
t_env	*create_env_element(char **value)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->bash_variable = value[0];
	element->bash_v_content = value[1];
	element->next = NULL;
	return (element);
}

/* Adding Elements to the back of the ENV List (Modified ft_lstadd_back) */
void	ft_lstadd_back_env_element(t_env **env_list, t_env *new)
{
	t_env	*temp;

	temp = *env_list;
	if (*env_list)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*env_list = new;
}

/* Printing the Elements from a Linked List */
void	print_env_list(t_env **env_list)
{
	t_env *temp;
	
	temp = *env_list;
	if (*env_list == NULL)
		printf("List is Empty\n");
	if (*env_list != NULL)
	{	
		while (temp->next != NULL)
		{
			printf("%s", "The Pointer of the Element: ");
			printf("%p\n", temp->next);
			printf("%s", "In List, bash_variable: ");
			printf("%s\n", temp->bash_variable);
			printf("%s", "In List, bash_v_content: ");
			printf("%s\n", temp->bash_v_content);
			temp = temp->next;
		}
		printf("%s", "In List: ");
		printf("%s\n", temp->bash_variable);
		printf("%s\n", temp->bash_v_content);
	}
}


/*				PARSER				*/
			
// // Pseudo Code:
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





/*             LEXAR				*/

/* Creating the Lexar Linked List with the Arguments from the Prompt */
void	create_lexar(t_list *lexar_list, char *line)
{
	int		i;
	char	**array;

	i = 0;
	array = ft_split(line, ' ');
	if (ft_strchr(line, '"'))
		array = ft_split(line, '"');
	else if (ft_strchr(line, '\''))
		array = ft_split(line, '\'');
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



/*		Second Try for PArser		*/
 
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