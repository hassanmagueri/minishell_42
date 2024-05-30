/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 22:43:35 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:12:53 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t__lst_token	*ft_next_token(t__lst_token **token)
{
	t__lst_token	*cur;

	cur = (*token)->next;
	while (cur && cur->type == WSP)
		cur = cur->next;
	return (cur);
}

t__lst_token	*ft_get_next_token_by_type(t__lst_token **lst_token,
					t_type type)
{
	t__lst_token	*cur;

	cur = *lst_token;
	while (cur)
	{
		if (cur->type == type)
			return (cur->next);
		cur = cur->next;
	}
	return (NULL);
}

t__lst_token	*ft_get_token_by_type(t__lst_token **lst_token, t_type type)
{
	t__lst_token	*cur;

	cur = *lst_token;
	while (cur)
	{
		if (cur->type == type)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
