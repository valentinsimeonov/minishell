/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 16:54:12 by smischni          #+#    #+#             */
/*   Updated: 2022/08/02 15:53:11 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../minishell.h"

typedef struct s_parser t_parser;
typedef struct s_env t_env;

int	check_builtins(t_parser *parser, t_env *env);

int	ft_echo(t_parser *parser);
int	echo_valid_flag(char *str);

int	ft_env(t_env *env, t_parser *parser);

int	ft_pwd(t_parser *parser);

#endif