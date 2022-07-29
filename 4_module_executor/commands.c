/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 14:31:21 by smischni          #+#    #+#             */
/*   Updated: 2022/07/29 14:23:21 by smischni         ###   ########.fr       */
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

	i = 0;
	parser->command = ft_calloc(count + 1, sizeof(char *));
	if (!parser->command)
		return (0);//error handling TBD
	while (sec)
	{
		if ((is_infile(sec->line) || is_outfile(sec->line)) && sec->next)
			sec = sec->next;
		else if (i == 0)
		{
			//check if builtin -> if yes: builtin flag + behaviours as in else; if not: strjoin with "/"
			parser->command[i] = ft_strjoin("/", sec->line);
		}
		else
			parser->command[i] = ft_strdup(sec->line);
		sec = sec->next;
		i++;
	}
	//condition: nur if builtin flag == 0
	add_path(parser);
	return (1);
}

/**
 * Checks if there is an executable for the command (first string in the command
 * array) in PATH. If not, it leaves the string as is, in case it is a binary 
 * with a specified path.
 * @param parser [t_parser *] Struct containing parsed input & relevant values.
 * @return [int] 1 at success, 0 at failure.
*/
int	add_path(t_parser *parser)//OPEN: PATH HAS TO BE ADJUSTED AFTER EVERY COMMAND INPUT -> VALENTIN
{
	int		i;
	char	*ex_path;

	i = 0;
	while (parser->paths[i])
	{
		ex_path = ft_strjoin(parser->paths[i++], parser->command[0]);
		if (!access(ex_path, F_OK) && !access(ex_path, X_OK))
		{
			free(parser->command[0]);
			parser->command[0] = ex_path;
			return (1);
		}
		free(ex_path);
	}
	return (1);
}
