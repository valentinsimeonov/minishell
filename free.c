#include "minishell.h"

void	free_minishell(t_data *data)
{
	// //  Freeing to_parser_list  
	// if (data->to_parser_list.sections)
	// 	free(data->to_parser_list.sections);
	// if (data->to_parser_list.sections)
	// 	ft_lstclear(data->to_parser_list.sections, free);

	// if (data->to_parser_list.paths)
	// 	free(data->to_parser_list.paths);
	
	// if (data->to_parser_list.command)
	// 	free(data->to_parser_list.command);
	// Maybe Need to Add Freeing for *line

	/* Freeing the Main Data Struct */
	if (data)
		free(data);
	// if (data)
	// 	ft_lstclear(data, free);

	//  Freeing to_env_list 
	// if (data->to_env_list->bash_variable)
	// 	free(data->to_env_list->bash_variable);
	// if (data->to_env_list->bash_variable)
	// 	free(data->to_env_list->bash_v_content);
	if (data->to_env_list)
		ft_lstclear_env(&data->to_env_list, free);
	
	// if (data->to_env_list.bash_v_content)
	// 	ft_lstclear(data->to_parser_list.sections, free);

	// if (data->to_env_list)
	// 	free(data);
}

void	ft_lstclear_env(t_env **lst, void (*del)(void *))
{
	t_env	*list;
	t_env	*temp;

	list = *lst;
	if (list != NULL)
	{
		while (list != NULL)
		{
			temp = list->next;
			ft_lstdelone_env(list, del);
			list = temp;
		}
	}
	*lst = NULL;
}

void	ft_lstdelone_env(t_env *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->bash_variable);
		del(lst->bash_v_content);
		free(lst);
	}
}
