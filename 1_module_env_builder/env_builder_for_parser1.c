/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder_for_parser1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:54:17 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/01 17:15:57 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_builder.h"

/* Initialises All Data */
t_data	*env_builder(char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->to_envp_data = initialise_envp(envp);
	data->to_parser_list.sections = ft_calloc(1, sizeof(t_list *));
	return (data);
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

/* Return the List that has Content Matches to_find string */
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

/* Returns pointer to Mallocked String - System Current Working Directory */
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
