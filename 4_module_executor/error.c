/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 13:52:14 by smischni          #+#    #+#             */
/*   Updated: 2022/08/09 16:19:42 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_error(int err_code, char *name, char *cust_mes)
{
	global_exit_status = err_code;
	if (name && ft_strncmp(name, "", 2) != 0)
		perror(name);
	else
	{
		ft_putstr_fd(cust_mes, 2);
		ft_putchar_fd('\n', 2);
	}
	return (1);
}
