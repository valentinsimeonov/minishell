/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:54:12 by smischni          #+#    #+#             */
/*   Updated: 2022/08/04 16:17:51 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

typedef struct s_parser t_parser;
typedef struct s_env t_env;

int		check_builtins(t_parser *parser, t_env *env);
t_env	*get_env(t_env *env, char *v_name);
t_env	*get_env_previous(t_env *env, char *v_name);

int		ft_cd(t_env *env, t_parser *parser, int flag_pipe);
int		cd_update_env(t_env *env, t_parser *parser);

int		ft_echo(t_parser *parser);
int		echo_valid_flag(char *str);

int		ft_env(t_env *env, t_parser *parser);

int		ft_exit(t_env *env, t_parser *parser, int flag_pipe);

int		ft_export(t_env *env, t_parser *parser, char **input, int flag_pipe);
int		export_handle_input(t_env *env, char *input);
int		export_add_variable(t_env *env, char **values);
int		export_print(t_env *env, t_parser *parser);
t_env	*export_get_next_smallest(t_env *small, t_env *env);
t_env	*export_check_oldpwd(t_env *small, t_env *next, t_env *env);

int		ft_pwd(t_parser *parser);

int		ft_unset(t_env *env, t_parser *parser, int flag_pipe);
int		unset_variable(t_env *env, t_parser *parser, int i);

#endif