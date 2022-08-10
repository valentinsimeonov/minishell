/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:30:34 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 17:57:21 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../minishell.h"
# include "../libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <string.h>

typedef struct s_data	t_data;

/* Signals */
void	signal_handler_parent(int signum);

#endif