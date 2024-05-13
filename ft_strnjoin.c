/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:08:47 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/13 17:02:40 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnjoin(char const *s1, char const *s2,unsigned int n, t_gc_type type)
{
	char	*res;
	int		i;
	size_t	size;
	int		lens1;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	size = n + lens1 + 1;
	// res = malloc(size);
	res = gc_alloc(size, type);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while ((unsigned int)(i - lens1) < n)
	{
		res[i] = s2[i - lens1];
		i++;
	}
	res[i] = 0;
	return (res);
}


/*
int main(int argc, char const *argv[])
{
	char *s = ft_strnjoin("hassan", "123456789");
	printf("%s\n", s);
	return 0;
}
*/
