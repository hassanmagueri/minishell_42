/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:41:20 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 21:53:38 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_spliter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	wordlen(char *str)
{
	int	i;

	i = 0;
	while (!is_spliter(str[i]) && str[i])
		i++;
	return (i);
}

int	count_words(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (is_spliter(s[i]))
			i++;
		if (s[i])
			count++;
		while (!is_spliter(s[i]) && s[i])
			i++;
	}
	return (count);
}

char	**ft_split_ws(char *str, t_gc_type type)
{
	char	**res;
	int		i;
	int		index;
	char	*word;
	int		j;

	(1) && (i = 0, index = 0);
	res = gc_alloc((count_words(str) + 1) * sizeof(char *), type);
	while (str[i] && index < count_words(str))
	{
		while (is_spliter(str[i]))
			i++;
		word = gc_alloc(wordlen(str + i) + 1, type);
		j = 0;
		while (j < wordlen(str + i))
		{
			word[j] = str[i + j];
			j++;
		}
		1 && (word[j] = '\0', res[index] = word);
		while (!is_spliter(str[i]) && str[i])
			i++;
		index++;
	}
	return (res[index] = NULL, res);
}
