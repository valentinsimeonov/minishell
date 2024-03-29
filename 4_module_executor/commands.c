/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:21 by smischni          #+#    #+#             */
/*   Updated: 2022/08/10 17:17:49 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * Takes all list elements that are not in- or outfiles and copies them in a
 * string array to be handed over to execve().
 * Finally, looks if an executable for the command exists and adds its path
 * to the first string of the command array. If there is no executable, it
 * leaves the first string as is, in case it is a binary outside of PATH.
 * @param count [int] Number of strings to be allocated.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @param sec [t_list *] List containing each word of the current input section.
 * @return [int] 1 at success, 0 at failure.
*/
int	create_command_array(int count, t_parser *parser, t_list *sec)
{
	int	i;
	int	test;

	i = 0;
	parser->command = ft_calloc(count + 1, sizeof(char *));
	if (!parser->command)
		return (0);
	while (sec)
	{
		if ((is_infile(sec->line) || is_outfile(sec->line)) && sec->next)
			sec = sec->next;
		else
			parser->command[i++] = ft_strdup(sec->line);
		sec = sec->next;
	}
	test = is_exec(parser, parser->command[0]);
	if (!is_builtin(parser->command[0]) && test < 2)
	{
		if (test == 1 || add_path(parser) == 0)
		{
			free_str_array(parser->command);
			return (0);
		}
	}
	return (1);
}

/**
 * Checks if there is an executable for the command (first string in the command
 * array) in PATH. If not, it leaves the string as is, in case it is a binary 
 * with a specified path.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @return [int] 1 at success, 0 at failure.
*/
int	add_path(t_parser *parser)
{
	int		i;
	char	*ex_path;
	char	*add_slash;

	i = 0;
	if (!parser->paths)
		return (1);
	add_slash = ft_strjoin("/", parser->command[0]);
	while (parser->paths[i])
	{
		ex_path = ft_strjoin(parser->paths[i++], add_slash);
		if (!access(ex_path, F_OK) && !access(ex_path, X_OK))
		{
			free(add_slash);
			free(parser->command[0]);
			parser->command[0] = ex_path;
			return (1);
		}
		free(ex_path);
	}
	free(add_slash);
	add_slash = ft_strjoin(parser->command[0], ": command not found");
	ft_error(parser, 127, NULL, add_slash);
	free(add_slash);
	return (0);
}

int	is_exec(t_parser *parser, char *cmd)
{
	if (ft_strncmp("./", cmd, 2) == 0 || ft_strncmp("/", cmd, 1) == 0
		|| ft_strncmp("../", cmd, 3) == 0)
	{
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (2);
			else
				ft_error(parser, 1, cmd, ": Permission denied");
		}
		else
			ft_error(parser, 1, cmd, ": No such file or directory");
		return (1);
	}
	return (0);
}
