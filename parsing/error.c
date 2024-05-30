/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:08:30 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 23:14:42 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *msg)
{
	if (msg == NULL)
		msg = "syntax error";
	ft_putendl_fd(msg, 2);
	return (1);
}

int	is_redirection(t_type type)
{
	if (type == INPUT || type == OUTPUT || type == APPEND || type == HEARDOC)
		return (1);
	return (0);
}

int	ft_ender_tokens(t__lst_token **tokens, t__lst_token *node)
{
	if (node == NULL)
		*tokens = NULL;
	else
		node->next = NULL;
	return (print_error(NULL));
}

int	ft_generate_errors_loop(t__lst_token **tokens, t__lst_token **cur_pointer,
		t__lst_token **prev, t__lst_token *next_node)
{
	t__lst_token	*cur;

	cur = *cur_pointer;
	while (cur)
	{
		next_node = ft_next_token(&cur);
		if ((cur->type == DOUB_Q || cur->type == SING_Q)
			&& ft_strlen(cur->str) == 1)
			return (ft_ender_tokens(tokens, *prev));
		if (is_redirection(cur->type))
		{
			if (next_node == NULL)
				return (ft_ender_tokens(tokens, *prev));
			else if (next_node
				&& (next_node->type == PIPE || is_redirection(next_node->type)))
				return (ft_ender_tokens(tokens, *prev));
		}
		else if (cur->type == PIPE && next_node && next_node->type == PIPE)
			return (ft_ender_tokens(tokens, *prev));
		if (cur->type != WSP)
			*prev = cur;
		cur = cur->next;
	}
	*cur_pointer = cur;
	return (0);
}

int	generate_errors(t__lst_token **tokens)
{
	t__lst_token	*prev;
	t__lst_token	*cur;

	cur = *tokens;
	prev = NULL;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
	{
		cur = NULL;
		return (print_error(NULL));
	}
	if (ft_generate_errors_loop(tokens, &cur, &prev, NULL))
		return (1);
	if (prev && prev->type == PIPE)
	{
		prev->next = NULL;
		return (print_error(NULL));
	}
	return (0);
}

	// ------******-------
	// while (cur)
	// {
	// 	next_node = ft_next_token(&cur);
	// 	if ((cur->type == DOUB_Q || cur->type == SING_Q)
		// && ft_strlen(cur->str) == 1)
	// 		return (ft_ender_tokens(tokens, prev));
	// 	if (is_redirection(cur->type))
	// 	{
	// 		if (next_node == NULL)
	// 			return (ft_ender_tokens(tokens, prev));
	// 		else if (next_node &&
	// 			(next_node->type == PIPE || is_redirection(next_node->type)))
	// 			return (ft_ender_tokens(tokens, prev));
	// 	}
	// 	else if (cur->type == PIPE && next_node && next_node->type == PIPE)
	// 		return (ft_ender_tokens(tokens, prev));
	// 	if (cur->type != WSP)
	// 		prev = cur;
	// 	cur = cur->next;
	// }
	// ------******-------