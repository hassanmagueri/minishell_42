/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_bSPACEk_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 05:44:16 by emagueri          #+#    #+#             */
/*   Updated: 2024/03/27 00:52:49 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_bSPACEk(t_list **lst, t_list *new)
{
	t_list	*lstlast;

	if (!lst)
		return ;
	lstlast = *lst;
	if (!lstlast)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}
