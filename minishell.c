/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 11:34:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/30 13:27:33 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	cwd[256];
	char	*line;
	char	space;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
	(void)argc;
	(void)argv;
	(void)envp;
	space = ' ';
	while (7)
	{
		line = readline(cwd);
		ft_split(line, space);
	}
	return (0);
}

