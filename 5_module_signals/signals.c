/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:30:36 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/20 10:13:07 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	handler(int	signum)
{
	if (signum == SIGINT/* && g_pid == 0*/)
	{
		ft_putstr_fd("\b\b\n", 1);
		// rl_replace_line("", 0); /// Only works on Linux
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signum == SIGINT/* && g_pid != */)
		ft_putstr_fd("\n", 1);
	else if (signum == SIGQUIT)
		ft_putstr_fd("\b\b\n", 1);
	// g_pid = 0;	
}

void	signal_check(t_data *data)
{
	struct sigaction	sa;

	t_data	*temp;
	temp = data;
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = &handler;
	// if (sigaction(SIGINT, &sa, NULL) == -1)
		// TODO  Insert Error Handling Function, Probably Saskia // err_handler(data, 0, NULL, "Minishell Does not Handle Ctrl+C");
	// if (sigaction(SIGQUIT, &sa, NULL) == -1)
		// TODO  Insert Error Handling Function, Probably Saskia // err_handler(data, 1, NULL, "Minishell Does not Handle Ctrl+D");
}





// //// *                                                   * //////
// /*
// /**
// 	@brief Makes new readline input line and delets input from last line
// 		Called on Ctrl+C. (Works properly on linux.)
// 	@param sig: Signal number.
// 	@return None.
// 	@exception Insert "rl_replace_line("", 0);" on line 29 to make it work
// 		properly.Aveliable only with linux readline library
// */
// static void	ft_sigint_handler(int sig)
// {
// 	if (sig == SIGINT && g_access.inter == 1)
// 	{
// 		printf("\b\b    ");
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

// /**
// 	@brief Ignores signal. Called on Ctrl+/.
// 	@param sig: Signal number.
// 	@return None.
// */
// static void	ft_sigquit_handler(int sig)
// {
// 	if (sig == SIGQUIT && g_access.inter == 1)
// 	{
// 		write(1, "\b\b  \b\b", 6);
// 		rl_redisplay();
// 	}
// }

// /**
// 	@brief Activates signal handeling of SIGQUIT (Ctrl+/)
// 		and SIGINT (Ctrl+C).
// 	@param sig: Signal number.
// 	@return None.
// */
// void	ft_signal_setup(void)
// {
// 	signal(SIGINT, ft_sigint_handler);
// 	signal(SIGQUIT, ft_sigquit_handler);
// }

// */