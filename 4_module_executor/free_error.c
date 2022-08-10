

#include "executor.h"

int	ft_error(t_parser *parser, int err_code, char *name, char *cust_mes)
{
	close_pipe_fd(parser);
	if (parser->input_fd > 2)
		close(parser->input_fd);
	if (parser->output_fd > 2)
		close(parser->output_fd);
	g_exit_status = err_code;
	if (name && ft_strncmp(name, "", 2) != 0)
		perror(name);
	else
	{
		ft_putstr_fd(cust_mes, 2);
		ft_putchar_fd('\n', 2);
	}
	return (1);
}

/**
 * Takes a string array as parameter and frees every string as well as the array.
 * @param str [char **] String array to be freed.
 * @return [int] 1 at success, 0 at failure.
*/
int	free_str_array(char **str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (1);
}

/**
 * Takes an array of lists and frees every list element and the list itself.
 * @param lists [t_list **] Array of lists.
 * @return [int] 1 at success, 0 at failure.
*/
int	free_lst_array(t_list **lists)
{
	int	i;

	if (!lists)
		return (1);
	i = 0;
	while (lists[i])
	{
		ft_lstclear(&lists[i], free);
		free(lists[i++]);
	}
	free(lists);
	return (1);
}
