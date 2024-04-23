/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/23 14:29:51 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_lst_redir(t_redir *redir);

t_redir	*ft_new_redir(char *file_name, t_type redirection_type)
{
	t_redir *cmds;

	cmds = malloc(sizeof(t_redir));
	cmds->file_name = file_name;
	cmds->redirection_type = redirection_type;
	cmds->next = NULL;
	return cmds;
}

int ft_add_back_redir(t_redir **redirs, t_redir *cmd)
{
	t_redir *cur;

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

t_cmd	*ft_new_cmd(char **cmd, t_redir **redir)
{
	t_cmd *cmds;

	cmds = malloc(sizeof(t_cmd));
	cmds->cmd = cmd;
	cmds->redir = *redir;
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

char	**ft_prepare_cmd(t__lst_token **tokens, t_redir **redirs)
{
	char **cmd;
	t__lst_token *last_token;
	t__lst_token *cur;
	int len = 0;
	int i = 0;
	
	last_token = *tokens;
	while (last_token && last_token->type != PIPE )
	{
		if (last_token->type == SPACE)
		{
			last_token = last_token->next;
			continue;
		}
		else if (last_token->type <= OUTPUT)
		{
			last_token = last_token->next;
			if (last_token && last_token->type == SPACE)
				last_token = last_token->next;
			if (last_token)
				last_token = last_token->next;
			continue;
		}
		len++;
		last_token = last_token->next;
	}
	cmd = malloc(sizeof(char *) * (len + 1));
	cur = *tokens;
	i = 0;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == SPACE)
		{
			cur = cur->next;
			continue;
		}
		else if (cur->type <= OUTPUT)
		{
			cur = cur->next;
			if (cur && cur->type == SPACE)
				cur = cur->next;
			ft_add_back_redir(redirs, ft_new_redir(cur->str, cur->type));
			if (cur)
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
	printf("[CMD]:");
	while (cur)
	{
		int i = 0;
		while (cur->cmd[i])
			printf("[%s]", cur->cmd[i++]);
		print_lst_redir(cur->redir);
		puts("");
		cur = cur->next;
	}
}

void print_lst_redir(t_redir *redir)
{
	t_redir *cur;

	cur = redir;
	printf("\n[FILES]:");
	while (cur)
	{
		printf("{%s}", cur->file_name);
		cur = cur->next;
	}
	puts("");
}

int ft_cmd(t_cmd **lst_cmd, t__lst_token **tokens)
{
	char **cmd_str;
	int	i = 0;
	t_redir **lst_redir;
	
	while (*tokens)
	{
		lst_redir = malloc(sizeof(t_redir *));
		*lst_redir = NULL;
		cmd_str = ft_prepare_cmd(tokens, lst_redir);
		t_cmd *cc = NULL;
		cc = ft_new_cmd(cmd_str, lst_redir);
		ft_add_back_cmd(lst_cmd, cc);
		// print_lst_redir(cc->redir);
		i++;
	}
	// print_lst_cmd(*lst_cmd);
	return 0;
}
