/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 09:29:47 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/19 09:52:32 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Checks All ENV Variables in the String and Resolves them, Returns 0 if Error */
int		env_creator(t_data *data, char **input)
{
	int		i;
	char	quote;
	char	*tmp;

	quote = 0;
	i = 0;
	while ((*input)[i])
	{
		if ((!quote /* || quote == " " */) && (*input)[i] == '$') // quote == "" -- This is Screwed Up 
		{
			tmp = check_and_get_env(data, *input, i);
			if (!tmp)
				return (0);
			free(*input);
			*input = tmp;
			if (!(*input)[i])
				break ;
		}
		else if (!quote && ((*input)[i] == '\'' || (*input)[i] == '"'))
			quote = (*input)[i];
		else if (quote && (*input)[i] == quote)
			quote = 0;
		i++;
	}
	return (1);
}

/* Check if ENV Variable is a Special Environment Variable  and REturns it if it Finds it, if not then Returns ENV from Original ENV */
char	*check_and_get_env(t_data *data, char *input, int index)
{
	char	*exit_status;
	char	*ret;

	index++;
	if (input[index] && input[index] == '?')
	{
		exit_status = ft_itoa(data->to_envp_data.exit_status);
		ret = str_replace_str_at(input, index - 1, 2, exit_status);
		free(exit_status);
		return (ret);
	}
	else
		return (replace_str_env(data, input, index));
}

/* Allocating a New String from a Value that will Replace the ENV Variable, Returns NULL if Error */
char	*replace_str_env(t_data *data, char *input, int index)
{
	char	*new_str;
	char	*env_value;
	int		len;

	len = 0;
	while (input[index] && (ft_isalpha(input[index]) || ft_isdigit(input[index]) || input[index] == '_'))
	{
		index++;
		len++;
		if (!(len - 1) && ft_isdigit(input[index - 1]))
			break;
	}
	new_str = ft_substr(input, index - len, len);
	if (!new_str)
		return (NULL);
	env_value = resolving_env(data->to_envp_data, new_str);
	free(new_str);
	if (!env_value)
		return (NULL);
	new_str = str_replace_str_at(input, index - len - 1, len + 1, env_value);
	free(env_value);
	return (new_str);
}

/* Find PWD and Returns it's Value in ENV List, PWD is Taken out of Memory */
char	*resolving_env(t_envp_data envp_data, char *env_name)
{
	if (!ft_strncmp(env_name, "PWD", 4))
		return (get_pwd(envp_data));
	else
		return (get_env_value(*envp_data.envp_cp, env_name));
}

/* Find PWD from the ENV, if not there it Get's it from Memory, Return NULL if Error */
char	*get_pwd(t_envp_data envp_data)
{
	char	*pwd;

	pwd = get_env_value(*envp_data.envp_cp, "PWD");
	if (!pwd)
		return (NULL);
	if (!ft_strlen(pwd))
	{
		if (!envp_data.pwd)
			return (ft_strdup(""));
		pwd = ft_strdup(envp_data.pwd);
		if (!pwd)
			return (NULL);
	}
	return (pwd);
}

/* Return New Allocated String, Old Substring Length with new Substring at Index */
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
	free(tmp);
	if (!new_str)
		return (NULL);
	return (new_str);
}
