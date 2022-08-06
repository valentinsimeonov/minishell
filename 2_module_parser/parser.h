

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

typedef struct s_data	t_data;
typedef struct s_env	t_env;

int	parser(t_data *data, char **line);

/* Parser's calls */
int		env_resolver(t_data *data, char **input);
int		lexer(char *line, t_list **clean_input);

int	split_into_commands(t_data *data, t_list **lexar_list);

void	print_list(t_list **stack);
void	free_array(char **arr);
char	*str_remove_char_at1(char *str, int idx);
int		ft_isspace(int c);
int		is_meta_char(int c);
char	*str_replace_str_at(char *str, int idx, int length, char *replacement);
int		char_array_len(char **arr);
int		is_str_redir(char *str);
void	perror(const char *s);
int		count_pipes_in_lexar_list(t_list **lexar_list);
char	*get_env_value(t_env **to_env_list, char *env);

#endif