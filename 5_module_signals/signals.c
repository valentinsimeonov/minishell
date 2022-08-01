/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:30:36 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/01 17:44:58 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/*   Check RREADME.md for Signal Translation and Architecture  */

void	signal_handler(int	signum)
{
	/* SIGINT == Ctrl + c */
	if (signum == SIGINT /* && PID == 0  Child Process */)
	{
		ft_putstr_fd("\b\b\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	global_exit_status = 1;
}


/* Still Need to Add this in the Function which Creates the Child */

/*
    signal(SIGINT, SIG_IGN);
	waitpid(vars->pid, &vars->tmp, 0);
	free(vars->path); //// This Should Probably not be Added
	signal(SIGINT, signal_handler);
	global_exit_status = WEXITSTATUS(vars->tmp);
*/



/* We need to Put a Signal Handler Function in The Function that Creates the Parent,
however we need to Put one in the Child Process as well */
 