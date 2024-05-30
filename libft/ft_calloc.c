/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:08:05 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 21:54:01 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size, int type)
{
	void	*res;
	int		i;

	i = 0;
	if ((long)count < 0 || (long) size < 0)
		return (NULL);
	res = gc_alloc(count * size, type);
	if (!res)
		return (0);
	ft_bzero(res, count * size);
	return (res);
}
