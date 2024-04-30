/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:04:02 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/29 18:25:40 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*res;
	int		len;

	len = 0;
	if (!s1)
		return NULL;
	while (s1[len])
		len++;
	res = malloc(len * sizeof(char) + 1);
	if (!res)
		return (0);
	res[len] = 0;
	while (len--)
		res[len] = s1[len];
	return (res);
}
