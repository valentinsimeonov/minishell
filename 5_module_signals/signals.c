/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:30:36 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/04 19:20:59 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/*   Check README.md for Signal Translation and Architecture  */
void	signal_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\b\b\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	global_exit_status = 1;
}
