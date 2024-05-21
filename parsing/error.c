/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:08:30 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/20 12:54:11 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int print_error(char *msg)
{
	// char *str;

	if (msg == NULL)
		msg = "syntax error";
	ft_putendl_fd(msg ,2);
	return 1;
}

int is_redirection(t_type type)
{
	if (type == INPUT || type == OUTPUT || type == APPEND || type == HEARDOC)
		return (1);
	return (0);
}

int generate_errors(t__lst_token **tokens)
{
	t__lst_token *prev;
	t__lst_token *next_node;
	t__lst_token *cur;
	static int enter_number;

	cur = *tokens;
	prev = NULL;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
	{
		cur = NULL;
		return print_error(NULL);
	}
	// while (cur && (enter_number != 0 && cur->type != HEARDOC))
	while (cur)
	{
		next_node = cur->next;
		if (next_node && next_node->type == WSP)
			next_node = next_node->next;
		if ((cur->type == DOUB_Q || cur->type == SING_Q) && ft_strlen(cur->str) == 1)
		{
			if (prev == NULL)
				*tokens = NULL;
			else 
				prev->next = NULL;
			return print_error(NULL);
		}
		if (is_redirection(cur->type))
		{
			if (next_node == NULL)
			{
				if (prev == NULL)
				*tokens = NULL;
				else 
					prev->next = NULL;
				return print_error(NULL);
			}
			else if ( next_node &&
				(next_node->type == PIPE || is_redirection(next_node->type)))
			{
				if (prev == NULL)
					*tokens = NULL;
				else 
					prev->next = NULL;
				return print_error(NULL);
			}
		}
		else if (cur->type == PIPE && next_node && next_node->type == PIPE)
		{
			if (prev == NULL)
				*tokens = NULL;
			else 
				prev->next = NULL;
			return print_error(NULL);
		}
		if (cur->type != WSP)
			prev = cur;
		cur = cur->next;
	}
	enter_number++;
	if (prev && prev->type == PIPE)
	{
		prev->next = NULL;
		return print_error(NULL);
	}
	return (0);
}
