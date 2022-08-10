/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:30:04 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 15:30:19 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*list;
	t_env	*temp;

	list = *lst;
	if (list != NULL)
	{
		while (list != NULL)
		{
			temp = list->next;
			ft_lstdelone_env(list, del);
			list = temp;
		}
	}
	*lst = NULL;
}

void	ft_lstdelone_env(t_env *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->bash_variable);
		del(lst->bash_v_content);
		free(lst);
	}
}
