/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:22:27 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/13 18:19:37 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_join(t__lst_token **lst_token)
{
	t__lst_token *prev;
	t__lst_token *cur;
	t__lst_token *cur_cmd;

	cur = *lst_token;
	// while (cur && cur->type != PIPE)
	while (cur)
	{
		cur_cmd = cur;
		while (cur_cmd && cur_cmd->type != WSP && cur_cmd->type != PIPE && cur_cmd->type > OUTPUT)
		{
			if (cur_cmd->type == DOUB_Q)
			{
				cur->type = DOUB_Q;
				cur_cmd->str = ft_strtrim(cur_cmd->str, "\"", ALLOC);
				printf("======> %s\n", cur_cmd->str);
			}
			else if (cur_cmd->type == SING_Q)
			{
				cur->type = SING_Q;
				cur_cmd->str = ft_strtrim(cur_cmd->str, "\'", ALLOC);
			}
			if (cur == cur_cmd)
			{
				cur_cmd = cur_cmd->next;
				continue;
			}
			prev = cur_cmd;
			cur->str = ft_strjoin(cur->str, cur_cmd->str, ALLOC);
			cur_cmd = cur_cmd->next;
		}
		if (cur != cur_cmd)
			cur->next = cur_cmd;
		cur = cur->next;
	}
	return (1);
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

