/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:11:09 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 13:15:18 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_join_value_lst(char *s1, char *s2, t_gc_type type)
{
	char	*res;
	int		i;
	size_t	size;
	int		lens1;

	if (!s1 && !s2)
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	size = ft_strlen((char *)s2) + lens1 + 1;
	res = gc_alloc(size, type);
	if (!res)
		return (NULL);
	i = 0;
	while (s2[i - lens1])
	{
		res[i] = s2[i - lens1];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
