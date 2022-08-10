/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 10:54:13 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 14:38:51 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_BUILDER_H
# define ENV_BUILDER_H

# include "../libft/libft.h"
# include "../minishell.h"

typedef struct s_data		t_data;
typedef struct s_envp_data	t_envp_data;
typedef struct s_env		t_env;

/*      Env Builder For Parser   */
t_list		**enviroment_list_con(char **envp);
t_data		*env_builder(char **envp);
t_list		*find_list(t_list *list, char *to_find, int exact_str);
char		*get_cwd(void);
char		*get_env_value(t_env **to_env_list, char *env);

/*      Env Builder Standalone   */
t_env		*create_env_list(char	**envp);
t_env		*create_env_element(char **value);
void		ft_lstadd_back_env_element(t_env **env_list, t_env *new);
void		print_env_list(t_env **env_list);

#endif