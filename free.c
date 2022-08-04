#include "minishell.h"

void	free_minishell(t_data *data)
{

	/* Freeing to_envp_list */
	if (data->to_envp_data.envp_cp)
		free(data->to_envp_data.envp_cp);
	if (data->to_envp_data.envp_cp)
		ft_lstclear(data->to_envp_data.envp_cp, free);

	if (data->to_envp_data.envp_empty)
		free(data->to_envp_data.envp_empty);
	if (data->to_envp_data.envp_empty)
		ft_lstclear(data->to_envp_data.envp_empty, free);


	if (data->to_envp_data.pwd_list)
		free(data->to_envp_data.pwd_list);
	if (data->to_envp_data.pwd_list)
		ft_lstclear(&data->to_envp_data.pwd_list, free);


	if (data->to_envp_data.old_pwd_list)
		free(data->to_envp_data.envp_empty);
	if (data->to_envp_data.old_pwd_list)
		ft_lstclear(&data->to_envp_data.old_pwd_list, free);


	if (data->to_envp_data.pwd)
		free(data->to_envp_data.pwd);

	if (data->to_envp_data.old_pwd)
		free(data->to_envp_data.old_pwd);

	/* Freeing to_parser_list  */
	if (data->to_parser_list.sections)
		free(data->to_parser_list.sections);
	if (data->to_parser_list.sections)
		ft_lstclear(data->to_parser_list.sections, free);

	if (data->to_parser_list.paths)
		free(data->to_parser_list.paths);
	
	if (data->to_parser_list.command)
		free(data->to_parser_list.command);
	// Maybe Need to Add Freeing for *line


	/* Freeing to_env_list */

	if (data->to_env_list.bash_variable)
		free(data->to_env_list.bash_variable);
	if (data->to_env_list.bash_variable)
		free(data->to_env_list.bash_v_content);
	// if (data.to_env_list)
	// 	ft_lstclear_env(data->to_env_list, free);
	
	// if (data->to_env_list.bash_v_content)
	// 	ft_lstclear(data->to_parser_list.sections, free);

	// if (data->to_env_list)
	// 	free(data);
}

// void	ft_lstclear_env(t_env **lst, void (*del)(void *))
// {
// 	t_env	*list;
// 	t_env	*temp;

// 	list = *lst;
// 	if (list != NULL)
// 	{
// 		while (list != NULL)
// 		{
// 			temp = list->next;
// 			ft_lstdelone(list, del);
// 			list = temp;
// 		}
// 	}
// 	*lst = NULL;
// }
