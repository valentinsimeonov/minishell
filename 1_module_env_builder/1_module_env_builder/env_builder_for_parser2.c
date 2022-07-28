/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder_for_parser2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:02:29 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/23 01:01:19 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_builder.h"

/* Returns New Allocated ENV Variable Value String from Name  */
char	*get_env_value(t_list *envp, char *env)
{
	char	*tmp;
	t_list	*list;
	int		value_start;
	int		to_free;

	to_free = 0;
	if (env[ft_strlen(env)] != '=')
	{
		tmp = ft_strjoin(env, "=");
		if (!tmp)
			return (NULL);
		env = tmp;
		to_free = 1;
	}
	value_start = ft_strlen(env);
	list = find_list(envp, env, 0);
	if (to_free)
		free(env);
	if (!list)
		return (ft_strdup(""));
	return (ft_substr(list->line,
			value_start, ft_strlen(list->line)));
}
