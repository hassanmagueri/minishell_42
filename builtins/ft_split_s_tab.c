/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_s_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:28:50 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/31 12:05:52 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_spliter(char c)
{
	return (c == ' ' || c == '\t');
}

int	len_word(char *str)
{
	int	len;

	len = 0;
	while (str[len] && !is_spliter(str[len]))
		len++;
	return (len);
}

static int	count_words(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (is_spliter(str[i]))
			i++;
		if (str[i])
			count++;
		while (!is_spliter(str[i]) && str[i])
			i++;
	}
	return (count);
}

char	**ft_split_space_tab(char *str, int type)
{
	char	**res;
	int		index;
	char	*word;
	int		j;
	int		i;

	index = 0;
	i = 0;
	res = gc_alloc((count_words(str) + 1) * sizeof(char *), type);
	if (!res)
		return (NULL);
	while (str[i] && index < count_words(str))
	{
		while (is_spliter(str[i]))
			i++;
		word = malloc(len_word(str + i) + 1);
		j = 0;
		while (str[i] && !is_spliter(str[i]))
			word[j++] = str[i++];
		word[j] = '\0';
		res[index++] = word;
	}
	res[index] = NULL;
	return (res);
}
