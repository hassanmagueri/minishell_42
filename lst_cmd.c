/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/20 18:08:08 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_new_cmd(char **cmd)
{
	t_cmd *cmds;

	cmds = malloc(sizeof(t_cmd));
	cmds->cmd = cmd;
	cmds->next = NULL;
	return cmds;
}

int ft_add_back_cmd(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd *cur;

	if (cmds == NULL || cmd == NULL)
		return (1);
	if (*cmds == NULL)
		*cmds = cmd;
	else
	{
		cur = *cmds;
		while (cur->next)
			cur = cur->next;
		cur->next = cmd;
	}
	return (0);
}

char	**ft_prepare_cmd(t__lst_token **tokens)
{
	char **cmd;
	t__lst_token *last_token;
	t__lst_token *cur;
	int len = 0;
	int i = 0;
	
	last_token = *tokens;
	while (last_token && last_token->type != PIPE)
	{
		if (last_token->type == SPACE)
		{
			last_token = last_token->next;
			continue;
		}
		len++;
		last_token = last_token->next;
	}
	cmd = malloc(sizeof(char *) * (len + 1));
	cur = *tokens;
	while (i < len)
	{
		if (cur->type == SPACE)
		{
			cur = cur->next;
			continue;
		}
		cmd[i++] = cur->str;
		cur = cur->next;
	}
	cmd[i] = NULL;
	if (cur)
		*tokens = cur->next;
	else
		*tokens  = NULL;
	if ((*tokens) && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
	return cmd;
}

void print_lst_cmd(t_cmd *cmd)
{
	t_cmd *cur;

	cur = cmd;
	while (cur)
	{
		int i = 0;
		while (cur->cmd[i])
			printf("[%s]", cur->cmd[i++]);
		puts("");
		cur = cur->next;
	}
	
}

int ft_cmd(t_cmd **lst_cmd, t__lst_token **tokens)
{
	char **cmd;
	int	i;
	
	while (*tokens)
	{
		cmd = ft_prepare_cmd(tokens);
		ft_add_back_cmd(lst_cmd, ft_new_cmd(cmd));
	}
	print_lst_cmd(*lst_cmd);
	// i = 0;
	// while (cmd[i])
	// 	printf("[%s]", cmd[i++]);
	// puts("");
	return 0;
}
