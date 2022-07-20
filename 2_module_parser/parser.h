/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:03:58 by vsimeono          #+#    #+#             */
/*   Updated: 2022/07/20 09:45:10 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "../minishell.h"
#include "../libft/libft.h"

typedef struct s_data	t_data;
typedef struct s_envp_data	t_envp_data;

/* Constructor */
int		constructor(t_data *data, char **line);
char	**get_paths_array(t_list *envp);
int		parser_error_handling(t_data *data, t_list **lexar_list, char **line, char *err);
int		free_parser(t_data *data, t_list **lexar_list, char **line, int clean_all);
void	free_array(char **arr);

/* Parser */
int			parser(t_list **lexar_list, char *line);
int			create_lexar_list(char *line, t_list **lexar_list, int *start, int *end);
int			is_invisible(int c);
int			remove_quotes(char **str);
char		*remove_char(char *str, int index);
void		finding_last_quote(char *line, int *end);
void		is_file_sign(char *line, int *end);
int			is_special_char(int c);

/* Command_splitter */
int	error(char *err, char **to_parser_list);
int	get_heredoc(char *stop_str);
int	get_inout_fd(t_data *data, t_list **list, char **to_parser_list);
int	array_addback(char ***array, char *str);
int	split_into_to_parser_lists(t_data *data, t_list *clean_input);
int	char_array_len(char **arr);
int	is_str_redir(char *str);

/* ENV Handler */
int		env_creator(t_data *data, char **input);
char	*check_and_get_env(t_data *data, char *input, int index);
char	*replace_str_env(t_data *data, char *input, int index);
char	*resolving_env(t_envp_data envp_data, char *env_name);
char	*get_pwd(t_envp_data envp_data);
char	*str_replace_str_at(char *str, int idx, int length, char *replacement);

/* Linked Lists Utils */
void		print_list(t_list **stack);
t_list		*create_element(char **value);

// Static
// int			parser(t_list **lexar_list, char *line);
// static int	create_lexar_list(char *line, t_list **lexar_list, int *start, int *end);
// int			is_invisible(int c);
// static int	remove_quotes(char **str);
// char		*remove_char(char *str, int index);
// static void	finding_last_quote(char *line, int *end);
// static void	is_file_sign(char *line, int *end);
// int			is_special_char(int c);

#endif
