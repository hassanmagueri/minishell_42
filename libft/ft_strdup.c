/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:04:02 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 21:55:27 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1, int type)
{
	char	*res;
	int		len;

	len = 0;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	res = gc_alloc(len * sizeof(char) + 1, type);
	if (!res)
		return (0);
	res[len] = 0;
	while (len--)
		res[len] = s1[len];
	return (res);
}
