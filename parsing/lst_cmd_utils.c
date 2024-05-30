/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:10:25 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*ft_new_redir(char *file_name, t_type redirection_type)
{
	t_redir	*cmds;

	cmds = gc_alloc(sizeof(t_redir), ALLOC);
	cmds->file_name = file_name;
	cmds->redirection_type = redirection_type;
	cmds->next = NULL;
	return (cmds);
}

int	ft_add_back_redir(t_redir **redirs, t_redir *cmd)
{
	t_redir	*cur;

	if (redirs == NULL || cmd == NULL)
		return (1);
	if (*redirs == NULL)
		*redirs = cmd;
	else
	{
		cur = *redirs;
		while (cur->next)
			cur = cur->next;
		cur->next = cmd;
	}
	return (0);
}

t_cmd	*ft_new_cmd(char **cmd, t_redir *redir)
{
	t_cmd	*cmds;

	cmds = gc_alloc(sizeof(t_cmd), ALLOC);
	cmds->cmd = cmd;
	cmds->redir = redir;
	cmds->next = NULL;
	return (cmds);
}

int	ft_add_back_cmd(t_cmd **cmds, t_cmd *cmd)
{
	t_cmd	*cur;

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

int	ft_len_cmd_part(t__lst_token **tokens)
{
	t__lst_token	*cur;
	int				len;

	len = 0;
	cur = *tokens;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == WSP || (cur->type == VAR && cur->str == NULL))
		{
			cur = cur->next;
			continue ;
		}
		else if (cur->type <= OUTPUT)
		{
			cur = cur->next;
			if (cur && cur->type == WSP)
				cur = cur->next;
			if (cur)
				cur = cur->next;
			continue ;
		}
		len++;
		cur = cur->next;
	}
	return (len);
}
