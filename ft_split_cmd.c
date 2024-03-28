/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:36:19 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/28 03:34:54 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_splitter(char c, char *sp)
{
	int i;

	i = 0;
	while (sp[i])
	{
		if (sp[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	count_word(char const *s, char *sp)
{
	int	i;
	int	count;

	count = 0;
	// if (s[0] != c && s[0])
	if (!is_splitter(s[0], sp) && s[0])
		count++;
	i = 1;
	while (i < ft_strlen(s))
	{
		// if (s[i] != c && s[i - 1] == c)
		if (!is_splitter(s[i], sp) && is_splitter(s[i - 1], sp))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strsdup(char const *s, int *index, char *sp)
{
	char	*str;
	int		len;
	int		i;

	len = 0;
	i = 0;
	// while (s[len] != c && s[len])
	while (!is_splitter(s[i], sp) && s[len])
		len++;
	str = malloc(len + 1);
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

static char	**freetab(char **res, int i)
{
	while (i--)
		free(res[i]);
	free(res);
	return (NULL);
}

char	**ft_split_cmd(char const *s, char *splitter)
{
	char	**res;
	int		i;
	int		index;

	index = 0;
	i = 0;
	if (!s)
		return (NULL);
	res = malloc((count_word(s, splitter) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < count_word(s, splitter) && s[index])
	{
		// while (s[index] == c)
		while (is_splitter(s[i], splitter))
			index++;
		printf("%d", index);
		res[i] = ft_strsdup(s + index, &index, splitter);
		if (!res[i])
			return (freetab(res, i));
		i++;
	}
	res[i] = NULL;
	return (res);
}

// int main(int argc, char const *argv[])
// {
// 	char **s = ft_split_cmd("ls a", "\"\'|<> ");
// 	int i = 0;
// 	while (s[i])
// 		printf("%s\n", s[i++]);
// 	return 0;
// }
