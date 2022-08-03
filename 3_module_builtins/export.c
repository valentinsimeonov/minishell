/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:16:47 by smischni          #+#    #+#             */
/*   Updated: 2022/08/03 19:37:46 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_export(t_env *env, t_parser *parser, char **input)
{
	int		i;

	i = 1;
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

int	export_print(t_env *env, t_parser *parser)
{
	t_env	*small;
	char	*old_small;
	t_env	*tmp;
	int		len;

	old_small = ft_strdup("");
	small = env->bash_variable;
	while(small != old_small)//condition does not make sense!!!!!!!
	{
		tmp = env;
		while (tmp)
		{
			len = ft_strlen(tmp->bash_variable);
			if (ft_strncmp(tmp->bash_variable, old_small, len) > 0)
			{
				if (ft_strncmp(tmp->bash_variable, small->bash_variable, len) < 0)
					small = tmp;
			}
			tmp = tmp->next;
		}
		ft_putstr_fd("declare -x ", parser->output_fd);
		ft_putstr_fd(small->bash_variable, parser->output_fd);
		if (small->bash_v_content)
		{
			ft_putchar_fd('=', parser->output_fd);
			ft_putstr_fd(small->bash_v_content, parser->output_fd);
		}
		ft_putchar_fd('\n', parser->output_fd);
		old_small = small->bash_variable;
	}
	return (1);
}
