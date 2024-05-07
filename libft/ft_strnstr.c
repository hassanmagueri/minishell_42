/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:13:44 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/04 22:05:05 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystSPACEk, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystSPACEk && len == 0)
		return (NULL);
	if (!(*needle))
		return ((char *)haystSPACEk);
	i = 0;
	while (haystSPACEk[i])
	{
		j = 0;
		while (haystSPACEk[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == 0)
				return ((char *)(haystSPACEk + i));
		}
		i++;
	}
	return (0);
}
