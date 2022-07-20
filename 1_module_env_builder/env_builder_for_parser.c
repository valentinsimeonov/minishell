/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder_for_parser.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:54:17 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/20 13:06:13 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_builder.h"

/* Creates the ENV List */
t_list	**enviroment_list_con(char **envp)
{
	t_list	**envp_cp;
	char	*env_vars_tmp;
	int		i;

	envp_cp = ft_calloc(1, sizeof(t_list *));
	*envp_cp = NULL;
	i = 0;
	while (envp[i])
	{
		env_vars_tmp = ft_strdup(envp[i]);
		ft_lstadd_back(envp_cp, ft_lstnew(env_vars_tmp));
		i++;
	}
	return (envp_cp);
}

/* Initialises ENV Data */
t_envp_data	initialise_envp(char **envp)
{
	t_envp_data	envp_data;
	char		*pwd;

	envp_data.envp_cp = enviroment_list_con(envp);
	envp_data.envp_empty = ft_calloc(1, sizeof(t_list *));
	*envp_data.envp_empty = NULL;
	envp_data.pwd_list = find_list(*envp_data.envp_cp, "PWD=", 0);
	pwd = get_cwd();
	if (!envp_data.pwd_list)
		ft_lstadd_back(envp_data.envp_cp, ft_lstnew(ft_strjoin("PWD=", pwd)));
	free(pwd);
	envp_data.pwd = get_env_value(*envp_data.envp_cp, "PWD");
	envp_data.old_pwd_list = find_list(*envp_data.envp_cp, "OLDPWD=", 0);
	if (!envp_data.old_pwd_list)
		ft_lstadd_back(envp_data.envp_empty, ft_lstnew(ft_strdup("OLDPWD")));
	envp_data.old_pwd = NULL;
	if (envp_data.old_pwd_list)
		envp_data.old_pwd = get_env_value(*envp_data.envp_cp, "OLDPWD");
	envp_data.exit_status = 0;
	return (envp_data);
}

/* Initialises All Data */
t_data	*env_builder(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->to_envp_data = initialise_envp(envp);
	data->to_parser_list.commands = ft_calloc(1, sizeof(t_list *));
	return (data);
}

// Return the list that has content matches to_find string
// Return NULL if couldn't find
t_list	*find_list(t_list *list, char *to_find, int exact_str)
{
	while (list)
	{
		if (!ft_strncmp((char *)list->line, to_find,
				ft_strlen(to_find) + (exact_str & 1)))
			break ;
		list = list->next;
	}
	return (list);
}

/* Returns pointer to malloced string - system current working dirrectory */
char	*get_cwd(void)
{
	char	*cwd;
	char	*buf;
	int		size;

	cwd = NULL;
	size = 1;
	while (!cwd)
	{
		buf = malloc(size);
		cwd = getcwd(buf, size);
		if (!cwd)
			free(buf);
		size++;
	}
	return (cwd);
}

// Return new allocated environment variable value string from name
// Return new allocated empty string if couldn't find
// Return NULL if error
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


