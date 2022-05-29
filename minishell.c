/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/29 14:41:33 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	
	char	*line;
	char	space;

	(void)argc;
	(void)argv;
	(void)envp;
	space = ' ';
	while (7)
	{
		line = readline("minishell> ");
		ft_split(line, space);
	}
	return (0);
}



// char	**ft_split(char const *s, char c)