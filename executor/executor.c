/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 11:39:46 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 18:08:33 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//executes every section (separated by pipes) after another
int	executor(t_parser *parser)
{
	t_list	*cur_sec;
	int		i;

	i = 0;
	while (parser->sections[i])
	{
		cur_sec = parser->sections[i++]; //requires libft to have a void pointer!!!
		//WIP
	}
	return (0);
}

int	exec_section(t_list *sec, t_parser *parser)
{
	//initializing fds to STDIN & STDOUT in case there is no infile / outfile
	parser->input_fd = STDIN_FILENO;
	parser->output_fd = STDOUT_FILENO;
	//prepare the command string array and open in-/outfiles
	if (exec_prep(sec, parser) != 0)
		return (0);// error handling TBD
	if (dup2(parser->input_fd, STDIN_FILENO) < 0)
		return (0);// error handling TBD
	if (dup2(parser->output_fd, STDOUT_FILENO))
		return (0);// error handling TBD
	//Thoughts: Pipen nicht notwendig wenn keine weitere Section; was ist wenn outfile innerhalb der Section, wie umgehen mit der letzten Section??
	//forks
	//checks the command -> check for built-ins, else search in PATH for binary
	//needs identifiers if child or parent i.e. for changing the env variables (ask Clemens)
}

int	exec_prep(t_list *sec, t_parser *parser)
{
	int		count;
	t_list	*head;

	count = 0;
	head = sec;
	//checking list elements:
	//if > or >> the next element is an infile
	//if < or << the next element is an outfile
	//else it is counted as a command to allocate enough memore for char **command
	while (head)
	{
		if (is_infile(head->line) == 1 && head->next)
		{
			infile(head->next->line, sec, parser, head->line);
			head = head->next;
		}
		else if (is_outfile(head->line) == 1 && head->next)
		{
			outfile(head->next->line, sec, parser, head->line);
			head = head->next;
		}
		else
			count++;
		head = head->next;
	}
	if (parser->input_fd < 0 || parser->output_fd < 0)
		return (0);//error handling TBD; only display message of the first invalid infile and outfile
	create_command_array(count, parser, sec); //error handling??
	return (1);
}

int	create_command_array(int count, t_parser *parser, t_list *sec)
{
	int	i;
	
	i = 0;
	parser->command = ft_calloc(count + 1, sizeof(char *));//remember to free after execution
	if (!parser->command)
		return(0);//error handling TBD
	while (sec)
	{
		if (is_infile(sec->line) == 1 || is_outfile(sec->line) == 1)
			sec = sec->next;
		else
			parser->command[i] = sec->line;
		sec = sec->next;
	}
	return (1);
}
