/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:35:52 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 18:52:36 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nlen(long n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	n /= 10;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n, t_gc_type type)
{
	long	ln;
	int		len;
	char	*res;

	ln = (long) n;
	if (n < 0)
		ln *= -1;
	len = nlen(ln);
	if (n < 0)
		len++;
	res = ft_calloc(len + 1, 1, type);
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	while (len-- && res[len] != '-')
	{
		res[len] = (ln % 10) + '0';
		ln /= 10;
	}
	return (res);
}
