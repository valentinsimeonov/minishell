/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 10:50:27 by smischni          #+#    #+#             */
/*   Updated: 2022/07/22 17:50:24 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	free_str_array(char **str)
{
	int	i;
	
	if (!str)
		return (1);
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (1);
}

int	free_lst_array(t_list **lists)
{
	int	i;

	if (!lists)
		return (1);
	i = 0;
	while (lists[i])
	{
		ft_lstclear(lists[i], free);
		free(lists[i++]);
	}
	free(lists);
	return (1);
}

char	**reassemble_env(t_env *env)
{
	t_env	*tmp;
	char	*tmp2;
	char	**envp;
	int		i;
	
	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	envp = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		tmp2 = ft_strjoin(env->bash_variable, "=");
		envp[i++] = ft_strjoin(tmp2, env->bash_v_content);
		free(tmp2);
		env = env->next;
	}
	return (envp);
}
