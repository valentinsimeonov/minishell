/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder_standalone.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 13:06:17 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/20 13:09:23 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_builder.h"

/*				ENV List			*/

/* Creating the ENV Linked List with the Arguments from the ENV */
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
		ft_lstadd_back_env_element(&env_list, create_env_element(array));
		i++;
	}
	// print_env_list(&env_list);
}

/* Creating One Element with Two Variables to Place in a Linked List */
t_env	*create_env_element(char **value)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->bash_variable = value[0];
	if (value[1] == NULL)
		element->bash_v_content = NULL;
	else
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
			printf("%s", "In List1, bash_variable: ");
			printf("%s\n", temp->bash_variable);
			printf("%s", "In List1, bash_v_content: ");
			printf("%s\n", temp->bash_v_content);
			temp = temp->next;
		}
		printf("%s", "In List2: ");
		printf("%s\n", temp->bash_variable);
		printf("%s\n", temp->bash_v_content);
	}
}
