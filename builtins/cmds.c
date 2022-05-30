/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danisanc <danisanc@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:38:41 by danisanc          #+#    #+#             */
/*   Updated: 2022/05/30 14:39:36 by danisanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"


void	print_pwd(char *cwd)
{
	if (getcwd(cwd, sizeof(cwd)) == NULL)
      perror("getcwd() error");
	printf("%s\n", cwd);
}

void	do_echo_n(char *echo_arg)
{
	printf("%s", echo_arg);
}

void	do_export(char	*new_var, char	**env)
{
	int	i;

	i = 0;
	while(env[i])
		i++;
	env[i] = malloc(ft_strlen(new_var) + 1);
	env[i + 1] = 0;
	ft_memcpy(env[i], new_var, ft_strlen(new_var) + 1);
}

void	do_unset(char	*var, char	**env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(var, get_var_name(env[i]), ft_strlen(var)))
		{
			//set variable to ' '?
		}
		i++;
	}
}

char	*get_var_name(char	*env_var)
{
	int		i;
	char	*var_name;
	int		name_len;

	i = 0;
	while(env_var[i])
	{
		if (env_var[i] = "=")
			break ;
		i++;
	}
	name_len = i;
	var_name = malloc(name_len + 1);
	i = 0;
	while(env_var[i])
	{
		var_name[i] = env_var[i];
		i++;
	}
	var_name[i] = 0;
	return (name_len);
}