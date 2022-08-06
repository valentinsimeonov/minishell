

#include "parser.h"

int	count_pipes_in_lexar_list(t_list **lexar_list)
{
	t_list	*head;
	int		pipe_counter;

	head = *lexar_list;
	pipe_counter = 1;
	while (head)
	{
		if (!ft_strncmp(head->line, "|", 2))
			pipe_counter++;
		head = head->next;
	}
	if (head)
		ft_lstclear(&head, free);
	return (pipe_counter);
}

/* Splits the Lexar List into Command List for executor */
int	split_into_commands(t_data *data, t_list **lexar_list)
{
	int		i;
	int		pipe_counter;
	t_list	*head;
	t_list	*head2;


	i = 0;
	head = *lexar_list;
	head2 = *lexar_list;

	pipe_counter = count_pipes_in_lexar_list(&head);
	data->to_parser_list.sections = ft_calloc(pipe_counter + 1, \
	sizeof(t_list *));
	while (head2)
	{
		if (is_str_redir(head2->line))
			ft_lstadd_back(&data->to_parser_list.sections[i], \
			ft_lstnew(head2->line));
		else if (!ft_strncmp(head2->line, "|", 2))
			i++;
		else if (!is_str_redir(head2->line))
		{
			ft_lstadd_back(&data->to_parser_list.sections[i], \
			ft_lstnew(head2->line));
		}
		head2 = head2->next;
	}
	if (head2)
		ft_lstclear(&head2, free);
	return (1);
}

/* Get Length of 2D Char Array */
int	char_array_len(char **arr)
{
	int	length;

	length = 0;
	while (arr[length])
		length++;
	return (length);
}

/* Return 1 if String is Redirected */
int	is_str_redir(char *str)
{
	if (!ft_strncmp(str, ">", 2)
		|| !ft_strncmp(str, ">>", 3)
		|| !ft_strncmp(str, "<", 2)
		|| !ft_strncmp(str, "<<", 3))
		return (1);
	return (0);
}
