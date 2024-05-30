/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:08:47 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 21:55:42 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, t_gc_type type)
{
	char	*res;
	int		i;
	size_t	size;
	int		lens1;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	size = ft_strlen((char *)s2) + lens1 + 1;
	res = gc_alloc(size, type);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - lens1])
	{
		res[i] = s2[i - lens1];
		i++;
	}
	res[i] = 0;
	return (res);
}
