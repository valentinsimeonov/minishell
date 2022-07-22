

#include "parser.h"

/*  Error handler */
static int	error(char *err, char **command)
{
	free_array(command);
	if (err)
		ft_putendl_fd(err, 2);
	else
		perror(err);
	return (0);
}

/* Adds one a String to Back of 2D Char Array */
static int	array_addback(char ***array, char *str)
{
	char	**tmp;

	if (!*array)
	{
		*array = ft_calloc(2, sizeof(char *));
		if (!*array)
			return (0);
		(*array)[0] = ft_strdup(str);
		if (!(*array)[0])
			return (0);
	}
	else
	{
		tmp = ft_calloc(char_array_len(*array) + 2, sizeof(char *));
		if (!tmp)
			return (0);
		ft_memmove(tmp, *array, char_array_len(*array) * sizeof(char *));
		tmp[char_array_len(*array)] = ft_strdup(str);
		if (!tmp[char_array_len(*array)])
			return (0);
		free(*array);
		*array = tmp;
	}
	return (1);
}

/* Splits the Lexar List into Command List for executor */
int	split_into_commands(t_data *data, t_list *clean_input)
{
	char	**command;

	command = NULL;
	while (clean_input)
	{
		if (is_str_redir(clean_input->line))
		{
			array_addback(&command, clean_input->line);
		}
		else if (!ft_strncmp(clean_input->line, "|", 2))
		{
			if (!command || !clean_input->next)
				return (error("syntax error near unexpected token `|'",
						command));
			ft_lstadd_back(data->to_parser_list.sections, ft_lstnew(command));
			command = NULL;
		}
		else if (!array_addback(&command, clean_input->line))
			return (error(NULL, command));
		clean_input = clean_input->next;
	}
	if (command)
		ft_lstadd_back(data->to_parser_list.sections, ft_lstnew(command));
	// printf("%s\n", command[0]);
	// printf("%s\n", command[1]);
	// printf("%s\n", command[2]);
	// printf("%s\n", command[3]);

	printf("In the Command Splitter");
	print_list(data->to_parser_list.sections);
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
