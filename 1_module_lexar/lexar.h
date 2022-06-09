/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:03:58 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/07 19:07:54 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXAR_H
#define LEXAR_H

#include "../minishell.h"

typedef struct s_all	t_all;

/* 1 Module Lexar */
void	create_lexar(t_list *lexar_list, char **array);
int		size_of_array(char **array);

	/* Linked Lists Utils */
t_list	*create_element(char **value);
void	print_list(t_list **stack);
void	free_list(t_list **list);
void	delete_list(t_list **list);

#endif