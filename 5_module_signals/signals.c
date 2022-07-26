/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:30:36 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/26 14:51:12 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handler(int	signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\b\b\n", 1);
		// rl_replace_line("", 0); /// Only works on Linux
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT)
		ft_putstr_fd("\n", 1);
	else if (signum == SIGQUIT)
		ft_putstr_fd("\b\b\n", 1);
}

void	signal_check(t_data *data)
{
	struct sigaction	sa;

	t_data	*temp;
	temp = data;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = &handler;
	// if (sigaction(SIGINT, &sa, NULL) == -1)
		
	// if (sigaction(SIGQUIT, &sa, NULL) == -1)
		// TODO  Insert Error Handling Function, ME
}
