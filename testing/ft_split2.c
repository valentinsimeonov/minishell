/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsimeono <vsimeono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 19:44:51 by vsimeono          #+#    #+#             */
/*   Updated: 2022/06/05 16:15:51 by vsimeono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
/*
*returns strings that are delimited by c
*/

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

static int	countingstrings(char const *s, char c);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);

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

char	**ft_split2(char const *s, char c)
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	lensrc;
	size_t	buffer;

	lensrc = ft_strlen(src);
	if (dstsize != 0)
	{
		if (lensrc >= dstsize)
		{
			buffer = dstsize - 1;
		}
		else
		{
			buffer = lensrc;
		}
		ft_memcpy(dst, src, buffer);
		*(dst + buffer) = '\0';
	}
	return (lensrc);
}

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*d;
	char	*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < (int) n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (dst);
}


int		main()
{
	char	*str;
	char	**array;
	int		i;

	str = "\"ls \"-la |\"grep arg |\"grep arg2\"";
	i = 0;
	array = ft_split2(str, '"');
	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i++;
	}
}