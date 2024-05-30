/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:53:36 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:23:02 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_gcfree_node(t_gc *node)
{
	free(node->content);
	free(node);
}

t_gc	*ft_gclast(t_gc **lst)
{
	t_gc	*cur;
	int		i;

	cur = *lst;
	if (!lst)
		return (0);
	i = 0;
	while (cur->next)
	{
		cur = cur->next;
		i++;
	}
	return (cur);
}

t_gc	*ft_gcnew(void *content, int alloc_for)
{
	t_gc	*lst;

	lst = malloc(sizeof(t_gc));
	if (!lst)
		return (NULL);
	lst->content = content;
	lst->alloc_for = alloc_for;
	lst->next = NULL;
	return (lst);
}

void	ft_gcadd_back(t_gc **lst, t_gc *new)
{
	t_gc	*lstlast;

	if (!lst)
		return ;
	new->next = NULL;
	lstlast = *lst;
	if (!lstlast)
	{
		*lst = new;
		return ;
	}
	ft_gclast(lst)->next = new;
}
