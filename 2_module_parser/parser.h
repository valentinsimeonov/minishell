/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:09:10 by vsimeono          #+#    #+#             */
/*   Updated: 2022/08/10 18:05:04 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

typedef struct s_data	t_data;
typedef struct s_env	t_env;

/* Constructor */
int		parser(t_data *data, char **line);
void	null_making(t_list *lexar);
void	free_array(char **arr);

/* Env Handler 1 and 2 */
int		env_resolver(t_data *data, char **input);
char	*str_replace_str_at(char *str, int idx, int length, char *replacement);
char	*get_env_value(t_env **to_env_list, char *env);

/* Final Command Builder */
int		count_pipes_in_lexar(t_list *lexar);
int		split_into_commands(t_data *data, t_list *lexar);
int		char_array_len(char **arr);
int		is_str_redir(char *str);

/* Parser 1 and 2 */
int		lexer(char *line, t_list **lexar_list);
char	*str_remove_char_at1(char *str, int idx);
int		ft_isspace(int c);
int		is_meta_char(int c);

#endif