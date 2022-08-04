/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:04:02 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 15:14:59 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(t_env *env, t_parser *parser)
{
	t_env	*previous;
	t_env	*searched;
	t_env	*following;
	int		i;

	i = 1;
	while (parser->command[i])
	{
		if (ft_strchr(parser->command[i], '='))
			ft_putstr_fd("unset: invalid identifier \'=\'", 2);//TBD, error message but continue with next argument
		else
		{
			searched = get_env(env, parser->command[i]);
			if (searched)
			{
				following = searched->next;
				previous = get_env_previous(env, parser->command[i]);
				previous->next = following;
				unset_free(searched);
			}
		}
		i++;
	}
	return (1);
}

int	unset_free(t_env *var)
{
	free(var->bash_variable);
	free(var->bash_v_content);
	free(var);
	return (1);
}
