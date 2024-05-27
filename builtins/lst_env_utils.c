/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:44:36 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 15:46:48 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst_env	*ft_lst_env_last(t_lst_env *lst)
{
	t_lst_env	*cur;

	cur = lst;
	if (!lst)
		return (NULL);
	while (cur->next)
		cur = cur->next;
	return (cur);
}

t_lst_env	*ft_new_env(char *key, char *value)
{
	t_lst_env	*node;

	node = gc_alloc(sizeof(t_lst_env), ALLOC_ENV);
	node->key = ft_strdup(key, ALLOC_ENV);
	node->value = ft_strdup(value, ALLOC_ENV);
	node->next = NULL;
	return (node);
}

char	*ft_get_env_val(t_lst_env **lst_env, char	*key)
{
	t_lst_env	*cur;

	cur = ft_get_env(lst_env, key);
	if (cur == NULL)
		return (NULL);
	return (cur->value);
}
