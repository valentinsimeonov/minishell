/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:04:53 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/31 10:21:52 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar.h"

// /* Creating the Lexar Linked List with the Arguments from the Prompt */
// void	create_lexar(t_list *lexar_list, char **array)
// {
// 	int		i;

// 	i = 0;
// 	while (i < size_of_array(array))
// 	{
// 		ft_lstadd_back(&lexar_list, create_element(&array[i]));
// 		i++;
// 	}
// 	print_list(&lexar_list);
// }

// /* Getting the Length of a 2D Array */
// int		size_of_array(char **array)
// {
// 	int		i;

// 	i = 0;
// 	while (array[i] != NULL)
// 		i++;
// 	return(i);
// }

// /* Creating One Element to Place in a Linked List */
// t_list	*create_element(char **value)
// {
// 	t_list	*element;

// 	element = malloc(sizeof(t_list));
// 	if (!element)
// 		return (NULL);
// 	element->line = *value;
// 	element->next = NULL;
// 	return (element);
// }

// /* Printing the Elements from a Linked List */
// void	print_list(t_list **stack)
// {
// 	t_list *temp_p;
	
// 	temp_p = *stack;
// 	if (*stack == NULL)
// 		printf("List is Empty\n");
// 	if (*stack != NULL)
// 	{	
// 		while (temp_p->next != NULL)
// 		{
// 			printf("%s", "In List: ");
// 			printf("%s\n", temp_p->line);
// 			temp_p = temp_p->next;
// 		}
// 		printf("%s", "In List: ");
// 		printf("%s\n", temp_p->line);
// 	}
// }