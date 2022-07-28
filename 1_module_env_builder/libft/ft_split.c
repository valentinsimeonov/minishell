/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:10:43 by vsimeono          #+#    #+#             */
/*   Updated: 2022/05/30 12:10:47 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
*returns strings that are delimited by c
*/
static int	countingstrings(char const *s, char c)
{
	size_t	i;
	int		result;

	result = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
			result++;
		}
		i++;
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	start;
	size_t	i;
	int		j;

	i = 0;
	start = 0;
	j = 0;
	result = malloc(sizeof(char *) * (countingstrings(s, c) + 1));
	if (!result)
		return (0);
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
			result[j] = malloc(sizeof(char) * (i - start + 2));
			ft_strlcpy(result[j++], &s[start], i - start + 2);
		}
		i++;
		start = i;
	}
	result[j] = NULL;
	return (result);
}
