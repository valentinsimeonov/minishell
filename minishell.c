/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/30 20:19:26 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char	*line;
	t_list	lexar_list;


	(void)argc;
	(void)argv;
	(void)envp;
	// while (7)
	// {
	// 	line = readline("minishell> ");
	// 	create_lexar(&lexar_list, ft_split(line, space));
	// }
	int		i;
	i = 0;
	char	**array;
	while (i < 3)
	{
		line = readline("minishell> ");
		// array = ft_split(line, ' ');
		// size_of_array(array);
		// printf("%s\n", array[0]);
		// printf("%d", size_of_array(array));
		// create_lexar(&lexar_list, array);
		create_lexar(&lexar_list, ft_split(line, ' '));
		// free_list(&lexar_list);
		// ft_lstclear(&lexar_list, (void (*)(void *))free_list);
		// free(line);
		delete_list(lexar_list);  ///   Doesn't Work to Delete the List
		// free(&line);
		i++;
	}
	return (0);
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

void	free_list(t_list **list)
{
    t_list    *tmp1;
    t_list    *tmp2;
    
    tmp1 = *list;
    while (tmp1 != NULL)
    {
        tmp2 = tmp1->next;
        free(tmp1);
        tmp1 = tmp2;
    }
}

void	create_lexar(t_list *lexar_list, char **array)
{
	int		i;

	i = 0;
	while (i < size_of_array(array))
	{
		ft_lstadd_back(&lexar_list, create_element(&array[i]));
		i++;
	}
	print_list(&lexar_list);
	// free(array);
}

int		size_of_array(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return(i);
}

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