/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/06 17:44:10 by vsimeono         ###   ########.fr       */
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
		line = readline("minishell:> ");
		// *lexar_list = create_lexar(&lexar_list, line);
		// create_lexar(&lexar_list, line);
		lexar(&lexar_list, line);
		// is_d_quotes_closed(lexar_list);
		i++;
	}
	// print_list(&lexar_list);
	// is_d_quotes_closed(lexar_list);
	return (0);
}


/*		LEXAR	Second Try 		*/

/*	Checking for Quotes, Sending the Line to the List Creating Function*/
int		lexar(t_list **lexar_list, char *line)
{
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (line[end])
	{
		if (line[end] == '"' || line[end] == '\'')
			finding_last_quote(line, &end);
		end++;
	}
	if (line[start] && !create_lexar_list(line, lexar_list, &start, &end))
		return (0);
	print_list(lexar_list);
	return (1);
}

/*	Dividing in to Substrings and Sending the Substrings to have the Quotes Removed, Creating the List */
static int	create_lexar_list(char *line, t_list **lexar_list, int *start, int *end)
{
	char	*content;
	
	content = ft_substr(line, *start, *end - *start);
	if (!content || !remove_quotes(&content))
		return (0);
	ft_lstadd_back(lexar_list, create_element(&content));
	
	return (78);
}

/*	Removing the Quotes */
static int	remove_quotes(char **str)
{
	int		i;
	char	quote;
	char	*temp;
	
	quote = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((!quote && ((*str)[i] == '"' || (*str)[i] == '\'')) || (quote && (*str)[i] == quote))
		{
			if (!quote && ((*str)[i] == '"' || (*str)[i] == '\''))
				quote = (*str)[i];
			else if (quote && (*str)[i] == quote)
				quote = 0;
			temp = remove_char(*str, i);
			free(*str);
			if (!temp)
				return (0);
			*str = temp;
		}
		else i++;
	}
	return (1);
}

/*	Removing Character from a String Function */
char	*remove_char(char *str, int index)
{
	char	*new_str;
	char	*start;

	if (!str || index < 0)
		return (NULL);
	if (index >= (int)ft_strlen(str))
	{
		return (str);
	}
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	if (!new_str)
		return (NULL);
	start = new_str;
	while (*str)
	{
		if (index == 0)
		{
			str++;
			if (!*str)
				break;
		}
		*new_str = *str;
		str++;
		new_str++;
		index--;
	}
	return(start);
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

/*	Finding the Last Quote	*/
static void	finding_last_quote(char *line, int *end)
{
	char	quote;

	quote = line[*end];
	(*end)++;
	while (line[*end] && quote != line[*end])
		(*end)++;
	if (line[*end])
		(*end)++;
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
















/*             LEXAR				*/

// /* Creating the Lexar Linked List with the Arguments from the Prompt */
// void	create_lexar(t_list **lexar_list, char *line)
// {
// 	char	**array;
// 	int		i;
	
// 	// char	*first_d_quote;
	
// 	i = 0;
// 	// while (line[i] != '\0')
// 	// {
// 	// 	if (ft_strchr(line, '"'))
// 	// 	{
// 	// 		first_d_quote = ft_strchr(line, '"');
// 	// 		if (!ft_strchr(first_d_quote, '"'))
// 	// 			printf("Double Quote not having Match\nPlease Try Again");
// 	// 		else if (ft_strchr(first_d_quote, '"'))
// 	// 			array = ft_split(line, '"');
// 	// 	}
// 	// }
// 	// char		*first_d_quote;
// 	// t_list	*temp;
// 	// temp = *lexar_list;
// 	// array = ft_split(line, ' ');
// 	array = NULL;
// 	if (ft_strchr(line, '"'))
// 		array = ft_split(line, '"');
// 	// else if (ft_strchr(line, '\''))
// 	// 	array = ft_split(line, '\'');
// 	while (i < size_of_array(array))
// 	{
// 		ft_lstadd_back(lexar_list, create_element(&array[i]));
// 		// if (ft_strchr(temp->line, '"'))
// 		// {
// 		// 	first_d_quote = ft_strchr(temp->line, '"');
// 		// 	if (!ft_strchr(first_d_quote, '"'))
// 		// 		printf("Double Quote not having Match\nPlease Try Again"); 
// 		// }
// 		i++;
// 	}
// 	print_list(lexar_list);
// 	// return (lexar_list);
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





// void	is_d_quotes_closed(t_list *lexar_list)
// {
// 	t_list		*temp;
// 	t_parser	*parser_list;
// 	char		*first_d_quote;

// 	// first_d_quote = NULL;
// 	temp = lexar_list;
// 	parser_list = NULL;

// 	while (temp->next != NULL)
// 	{
// 		if (ft_strchr(temp->line, '"'))
// 		{
// 			first_d_quote = ft_strchr(temp->line, '"');
// 			if (!ft_strchr(first_d_quote, '"'))
// 				printf("Double Quote not having Match\nPlease Try Again"); // 
// 		}
// 		temp = temp->next;
// 	}
// 	if (ft_strchr(temp->line, '"'))
// 		{
// 			first_d_quote = ft_strchr(temp->line, '"');
// 			if (!ft_strchr(first_d_quote, '"'))
// 				printf("Double Quote not having Match\nPlease Try Again"); // 
// 		}
// 	printf("Double Quote is Closed");
// }















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





/*		Second Try for Parser		*/
 
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




	// if (ft_strchr(line, '"'))
	// 	{
	// 		first_d_quote = ft_strchr(line, '"');
	// 		if (!ft_strchr(first_d_quote, '"'))
	// 			printf("Double Quote not having Match\nPlease Try Again");
	// 		else if (ft_strchr(first_d_quote, '"'))
	// 			array = ft_split(line, '"');
	// 	}












	



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