/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:53:36 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/11 01:09:55 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_gcfree_node(t_gc *node)
{
	t_gc	*cur;
	
	// printf("%s--------\n", (char *)node->content);
	free(node->content);
	free(node);
}

t_gc	*ft_gclast(t_gc **lst)
{
	t_gc	*cur;

	cur = *lst;
	if (!lst)
		return (0);
	int i = 0;
	while (cur->next)
	{
		// printf("i = %d\n", i);
		// printf("%p\n", cur->content);
		cur = cur->next;
		i++;
	}
	return (cur);
}

static t_gc	*ft_gcnew(void *content, int alloc_for)
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

static void	ft_gcadd_back(t_gc **lst, t_gc *new)
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

// void	*gc_alloc(size_t size, void *new_ptr, int type)

void *free_gc(t_gc **lst, int type)
{
	t_gc	*cur;
	t_gc	*head;
	t_gc	*next;
	
	cur = *lst;
	next = NULL;
	head = NULL;
	// if (type == FREE_ENV)
		
	while (cur)
	{
		next = cur->next;
		// if (cur->alloc_for != type - 2)
		// if (type == FREE_ENV)
		// 	ft_gcfree_node(cur);
		if (cur->alloc_for == ALLOC_ENV)
			ft_gcadd_back(&head, cur);
		// else if (cur->alloc_for == type - 2)
		else if (cur->alloc_for == ALLOC)
			ft_gcfree_node(cur);
		cur = next;
	}
	*lst = head;
	return (NULL);
}

void	*gc_alloc(size_t size, t_gc_type type)
{
	void	*ptr;
	static t_gc *head;
	static t_gc *prev;
	t_gc *new;

	if (type == ALLOC || type == ALLOC_ENV)
	{
		ptr = malloc(size);
		if (ptr == NULL)
			return free_gc(&head, type);
		new = ft_gcnew(ptr, type);
		if (head == NULL)
			head = new;
		else
		{
			ft_gcadd_back(&head, new);
			// prev->next = new;
		}
		prev = new;
	}
	else if (type == FREE || type == FREE_ENV)
		free_gc(&head, type);
	return ptr;
}
