/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:22:27 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/31 16:42:11 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_join_token(t_lst_token **cur_pointer, t_lst_token **cur_cmd_pointer)
{
	t_lst_token	*cur_cmd;
	t_lst_token	*cur;

	(1) && (cur_cmd = *cur_pointer, cur = *cur_pointer);
	while (cur_cmd && cur_cmd->type != WSP
		&& cur_cmd->type != PIPE && cur_cmd->type > OUTPUT)
	{
		if (cur_cmd->type == DOUB_Q)
			cur->type = DOUB_Q;
		else if (cur_cmd->type == SING_Q)
			cur->type = SING_Q;
		if (cur == cur_cmd)
		{
			cur_cmd = cur_cmd->next;
			continue ;
		}
		if (cur->str == NULL)
			cur->str = ft_strdup(cur_cmd->str, ALLOC);
		else if (cur_cmd->str == NULL)
			cur->str = ft_strdup(cur->str, ALLOC);
		else
			cur->str = ft_strjoin(cur->str, cur_cmd->str, ALLOC);
		cur_cmd = cur_cmd->next;
	}
	return (*cur_pointer = cur, *cur_cmd_pointer = cur_cmd, 1);
}

int	ft_join(t_lst_token **lst_token)
{
	t_lst_token	*cur;
	t_lst_token	*cur_cmd;

	cur = *lst_token;
	while (cur)
	{
		ft_join_token(&cur, &cur_cmd);
		if (cur != cur_cmd)
			cur->next = cur_cmd;
		cur = cur->next;
	}
	return (0);
}
