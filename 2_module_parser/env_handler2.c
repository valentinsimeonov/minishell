/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 14:20:40 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/05 19:42:17 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Return New Allocated String, Old Substring Length with \ 
   new Substring at Index */
char	*str_replace_str_at(char *str, int idx, int length, char *replacement)
{
	char	*new_str;
	char	*tmp;

	if (!str || idx < 0 || length < 0 || !replacement)
		return (NULL);
	if (idx >= (int)ft_strlen(str))
		return (ft_strjoin(str, replacement));
	if (length > (int)ft_strlen(&str[idx]))
		length = (int)ft_strlen(&str[idx]);
	str[idx] = '\0';
	tmp = ft_strjoin(str, replacement);
	if (!tmp)
		return (NULL);
	new_str = ft_strjoin(tmp, &str[idx + length]);
	if (tmp)
		free(tmp);
	if (!new_str)
		return (NULL);
	return (new_str);
}

/* Returns New Allocated ENV Variable Value String from Name  */
char	*get_env_value(t_env **to_env_list, char *env)
{
	t_env	*temp;
	int		variable_length;
	
	temp = *to_env_list;
	variable_length = ft_strlen(env);
	while (temp)
	{
		if (!ft_strncmp(temp->bash_variable, env, variable_length))
			return (temp->bash_v_content);
		temp = temp->next;
	}
	// if (!to_env_list)
	return (ft_strdup(""));
}