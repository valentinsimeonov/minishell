/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smischni <smischni@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 10:30:21 by smischni          #+#    #+#             */
/*   Updated: 2022/07/20 11:39:15 by smischni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*trim_redirect(char *file, char c)
{
	int		i;
	int		j;
	char	*filename;

	if (!file)
		return (NULL);
	i = 0;
	j = 0;
	while (file[i] && file[i] == c)
		i++;
	while (file[i] && file[i] == ' ')//tbd: What if there are multiple spaces??
		i++;
	filename = ft_calloc(ft_strlen(file) - i + 1, sizeof(char));
	if (!filename)
		return (NULL);
	while (file[i])
		filename[j++] = file[i++];
	return (filename);
}
