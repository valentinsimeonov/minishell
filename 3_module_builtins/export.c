/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:16:47 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 16:00:33 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_env *env, t_parser *parser, char **input, int flag_pipe)
{
	int		i;

	i = 1;
	if (flag_pipe == 1)
		return (1);
	if (!input[i])
		export_print(env, parser);
	else
	{
		while (input[i])
			export_handle_input(env, input[i++]);
	}
	return (1);
}

int	export_handle_input(t_env *env, char *input)
{
	char	*values[2];
	int		j;

	j = 0;
	if (input[j] == '=')
		return (0);//error handling tbd: export: `=': not a valid identifier
	while (input[j] && input[j] != '=')
		j++;
	values[0] = ft_calloc(j + 1, sizeof(char));
	ft_memcpy(values[0], input, j);
	if (input[j++] == '=')
	{
		values[1] = ft_calloc(ft_strlen(input) - j + 1, sizeof(char));
		ft_memcpy(values[1], &input[j], ft_strlen(input) - j);
	}
	else
		values[1] = NULL;
	export_add_variable(env, values);
	return (1);
}

int	export_add_variable(t_env *env, char **values)
{
	t_env	*tmp;

	tmp = get_env(env, values[0]);
	if (tmp)
	{
		if (tmp->bash_v_content)
			free(tmp->bash_v_content);
		tmp->bash_v_content = values[1];
	}	
	else
		ft_lstadd_back_env_element(env, create_env_element(values));
	return (1);
}
