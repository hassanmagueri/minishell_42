/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:36:19 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 21:47:09 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	if (s[0] != c && s[0])
		count++;
	i = 1;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && s[i - 1] == c)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strsdup(char const *s, int *index, char c, int type)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len] != c && s[len])
		len++;
	str = gc_alloc(len + 1, type);
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	*index += i;
	return (str);
}

// static char	**freetab(char **res, int i)
// {
// 	while (i--)
// 		free(res[i]);
// 	free(res);
// 	return (NULL);
// }

char	**ft_split(char *s, char c, int type)
{
	char	**res;
	int		i;
	int		index;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	res = gc_alloc((count_word(s, c) + 1) * sizeof(char *), type);
	if (!res)
		return (NULL);
	while (i < count_word(s, c) && s[index])
	{
		while (s[index] == c)
			index++;
		res[i] = ft_strsdup(s + index, &index, c, type);
		i++;
	}
	res[i] = NULL;
	return (res);
}
