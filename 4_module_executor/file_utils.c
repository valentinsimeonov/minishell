/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:18:55 by smischni          #+#    #+#             */
/*   Updated: 2022/08/10 10:53:52 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	open_files_count_cmds(t_parser *parser, t_list *sec)
{
	int		count;
	t_list	*head;

	count = 0;
	head = sec;
	while (head)
	{
		if (is_infile(head->line) == 1 && head->next)
		{
			infile((char *)head->next->line, parser, (char *)head->line);
			head = head->next;
		}
		else if (is_outfile(head->line) == 1 && head->next)
		{
			outfile((char *)head->next->line, parser, (char *)head->line);
			head = head->next;
		}
		else
			count++;
		head = head->next;
	}
	return (count);
}

int	set_fds(t_parser *parser, int i)
{
	parser->input_fd = STDIN_FILENO;
	if (parser->sections[i])
		parser->output_fd = STDIN_FILENO;
	else
		parser->output_fd = STDOUT_FILENO;
	parser->pipe_fd[0] = 0;
	parser->pipe_fd[1] = 0;
	return (1);
}

int	store_fds(t_parser *parser)
{
	parser->store_stdin = dup(STDIN_FILENO);
	parser->store_stdout = dup(STDOUT_FILENO);
	return (1);
}

int	restore_std_fds(t_parser *parser)
{
	if (dup2(parser->store_stdin, 0) < 0 || dup2(parser->store_stdout, 1) < 0)
	{
		close(parser->store_stdin);
		close(parser->store_stdout);
		return (0);
	}
	close(parser->store_stdin);
	close(parser->store_stdout);
	return (1);
}

int	close_pipe_fd(t_parser *parser)
{
	if (parser->pipe_fd[0] > 2)
		close(parser->pipe_fd[0]);
	if (parser->pipe_fd[1] > 2)
		close(parser->pipe_fd[1]);
	parser->pipe_fd[0] = 0;
	parser->pipe_fd[1] = 0;
	return (1);
}
