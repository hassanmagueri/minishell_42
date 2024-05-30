/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:41:16 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 21:56:07 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, int type)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if ((unsigned int)ft_strlen(s) <= start)
		return (ft_strdup("", type));
	if (len > ft_strlen(s) - start)
		return (ft_strdup(s + start, type));
	res = gc_alloc(len + 1, type);
	if (!res)
		return (NULL);
	while (*(s + start + i) && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = 0;
	return (res);
}
