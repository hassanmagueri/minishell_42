/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:53:36 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/31 17:20:40 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*free_gc(t_gc **lst)
{
	t_gc	*cur;
	t_gc	*next;

	cur = *lst;
	next = NULL;
	while (cur)
	{
		next = cur->next;
		ft_gcfree_node(cur);
		cur = next;
	}
	*lst = NULL;
	return (NULL);
}

void	*free_gc_env(t_gc **lst)
{
	t_gc	*cur;
	t_gc	*next;

	cur = *lst;
	next = NULL;
	while (cur)
	{
		next = cur->next;
		ft_gcfree_node(cur);
		cur = next;
	}
	*lst = NULL;
	return (NULL);
}

void	*ft_alloc(t_gc **head, t_gc **prev, size_t size, t_gc_type type)
{
	void			*ptr;
	t_gc			*new;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	new = ft_gcnew(ptr, type);
	if (*head == NULL)
		*head = new;
	else
		ft_gcadd_back(head, new);
	*prev = new;
	return (ptr);
}

void	*gc_alloc(size_t size, t_gc_type type)
{
	void			*ptr;
	static t_gc		*head;
	static t_gc		*head_env;
	static t_gc		*prev;
	static t_gc		*prev_env;

	ptr = NULL;
	if (type == ALLOC)
	{
		ptr = ft_alloc(&head, &prev, size, type);
		if (ptr == NULL)
			return (free_gc(&head), free_gc_env(&head_env), exit(1), NULL);
	}
	else if (type == ALLOC_ENV)
	{
		ptr = ft_alloc(&head_env, &prev_env, size, type);
		if (ptr == NULL)
			return (free_gc(&head), free_gc_env(&head_env), exit(1), NULL);
	}
	else if (type == FREE)
		free_gc(&head);
	else if (type == FREE_ENV)
		free_gc_env(&head_env);
	return (ptr);
}
