/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:36:44 by emagueri          #+#    #+#             */
/*   Updated: 2024/06/01 09:57:17 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_trim(t_lst_token **lst_token)
{
	t_lst_token	*cur;

	cur = *lst_token;
	while (cur)
	{
		if (cur->type == DOUB_Q)
			cur->str = ft_strtrim(cur->str, "\"", ALLOC);
		else if (cur->type == SING_Q)
			cur->str = ft_strtrim(cur->str, "\'", ALLOC);
		cur = cur->next;
	}
	return (1);
}

int	ft_parsing(t_lst_token **lst_token, t_lst_env **lst_env, t_cmd **lst_cmd,
			int *exit_status)
{
	int	is_error;

	is_error = generate_errors(lst_token);
	ft_trim(lst_token);
	if (is_error)
	{
		ft_fake_heredoc(lst_token);
		gc_alloc(0, FREE);
		*exit_status = 258;
		return (258);
	}
	if (*lst_token == NULL)
		return (1);
	ft_expand(lst_token, lst_env, exit_status);
	ft_join(lst_token);
	ft_heredoc(lst_token, lst_env, *exit_status);
	if (*lst_token == NULL)
		return (1);
	ft_cmd(lst_cmd, lst_token);
	return (0);
}
