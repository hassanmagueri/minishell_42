/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:22:27 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/21 17:15:55 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int ft_is_space_middle(t__lst_token **lst_token, char *str)
// {
// 	t__lst_token	*cur;
// 	char			*new_str;
// 	int				i;

// 	cur = *lst_token;
// 	while (cur && cur->type == VAR)
// 	{
		
// 	}
	
// 	i = 0;
// 	new_str = ft_strtrim(str, " ", ALLOC);
// 	while (new_str[i])
// 		if (new_str[i++] == ' ')
// 			return 1;
// 	return (0);
// }

int ft_ambiguous(t__lst_token **lst_token)
{
	t__lst_token *cur;
	t__lst_token *tmp;

	cur = *lst_token;
	while (cur)
	{
		tmp = cur->next;
		if (cur->type == OUTPUT)
		{
			if (tmp->type == WSP)
				tmp = tmp->next;
			if (tmp->type == VAR && tmp->str == NULL)
					return print_error("ambiguous redirect\n");
			// else if (tmp->type == VAR && ft_is_space_middle(tmp->str))
		}
		cur = cur->next;
	}
	return 0;
}

int ft_join(t__lst_token **lst_token)
{
	t__lst_token *prev;
	t__lst_token *cur;
	t__lst_token *cur_cmd;

	cur = *lst_token;
	while (cur)
	{
		cur_cmd = cur;
		while (cur_cmd && cur_cmd->type != WSP && cur_cmd->type != PIPE && cur_cmd->type > OUTPUT)
		{
			if (cur_cmd->type == DOUB_Q)
				cur->type = DOUB_Q;
				// cur_cmd->str = ft_strtrim(cur->str, "\"", ALLOC);
			else if (cur_cmd->type == SING_Q)
				cur->type = SING_Q;
			if (cur == cur_cmd)
			{
				cur_cmd = cur_cmd->next;
				continue;
			}
			prev = cur_cmd;
			if (cur->str == NULL)
				cur->str = ft_strdup(cur_cmd->str, ALLOC);
			else if (cur_cmd->str == NULL)
				cur->str = ft_strdup(cur->str, ALLOC);
			else
				cur->str = ft_strjoin(cur->str, cur_cmd->str, ALLOC);
			cur_cmd = cur_cmd->next;
		}
		if (cur != cur_cmd)
			cur->next = cur_cmd;
		cur = cur->next;
	}
	return (ft_ambiguous(lst_token));
}

// int main(int argc, char const *argv[])
// {
// 	t__lst_token *token;
	
// 	// ft_lst_token_add_back(&token, ft_new_token("\"s\"", DOUB_Q));
// 	// ft_lst_token_add_back(&token, ft_new_token(">", OUTPUT));
// 	// ft_lst_token_add_back(&token, ft_new_token("ls", WORD));
// 	// ft_lst_token_add_back(&token, ft_new_token("WSP", WSP));
// 	ft_lst_token_add_back(&token, ft_new_token("<<", HEARDOC));
// 	ft_lst_token_add_back(&token, ft_new_token("", WORD));
// 	ft_lst_token_add_back(&token, ft_new_token("EOF", DOUB_Q));
// 	// ft_lst_token_add_back(&token, ft_new_token("\"s\"", DOUB_Q));
// 	// ft_lst_token_add_back(&token, ft_new_token("WSP", WSP));
// 	// ft_lst_token_add_back(&token, ft_new_token("-a", WORD));
// 	ft_join(&token);
// 	print__lst_tokens(token);
// 	return 0;
// }

