/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/24 22:15:25 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_lst_redir(t_redir *redir);

t_redir	*ft_new_redir(char *file_name, t_type redirection_type)
{
	t_redir *cmds;

	cmds = gc_alloc(sizeof(t_redir), ALLOC);
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

t_cmd	*ft_new_cmd(char **cmd, t_redir *redir, int len)
{
	t_cmd *cmds;

	// cmds = malloc(sizeof(t_cmd));
	cmds = gc_alloc(sizeof(t_cmd), ALLOC);
	cmds->cmd = cmd;
	cmds->redir = redir;
	cmds->len = len;
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

char	**ft_prepare_cmd(t__lst_token **tokens, t_redir **redirs, int *lens)
{
	char **cmd;
	t__lst_token *last_token;
	t__lst_token *cur;
	int len = 0;
	int i = 0;
	
	last_token = *tokens;
	while (last_token && last_token->type != PIPE )
	{
		if (last_token->type == WSP)
		{
			last_token = last_token->next;
			continue;
		}
		else if (last_token->type <= OUTPUT)
		{
			last_token = last_token->next;
			if (last_token && last_token->type == WSP)
				last_token = last_token->next;
			if (last_token)
				last_token = last_token->next;
			continue;
		}
		len++;
		last_token = last_token->next;
	}
	// printf("len : %d\n", len);
	*lens = len - 1;
	cmd = gc_alloc(sizeof(char *) * (len + 1), ALLOC);
	cur = *tokens;
	i = 0;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == WSP)
		{
			cur = cur->next;
			continue;
		}
		else if (cur->type <= OUTPUT)
		{
			t_type type;
			type = cur->type;
			cur = cur->next;
			if (cur && cur->type == WSP)
				cur = cur->next;
			ft_add_back_redir(redirs, ft_new_redir(cur->str, type));
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

void print_lst_cmd(t_cmd **cmd)
{
	t_cmd *cur;

	cur = *cmd;
	while (cur)
	{
		int i = 0;
		printf("[CMD]:");
		while (cur->cmd && cur->cmd[i])
			printf("[%s]", cur->cmd[i++]);
		print_lst_redir(cur->redir);
		printf("\n");
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
	printf("\n");
}

int	*ft_add_int(int **ref_arr, int *len, int n)
{
	int *res;
	int *arr;
	int i;

	arr = *ref_arr;
	i = 0;
	// res = malloc(((*len) + 1) * sizeof(int));
	res = gc_alloc(((*len) + 1) * sizeof(int), ALLOC);
	while (i < *len)
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = n;
	(*len) += 1;
	// free(arr);
	*ref_arr = res;
	return (res);
}

int ft_cmd(t_cmd **lst_cmd, t__lst_token **tokens)
{
	char **cmd_str;
	int	i = 0;
	int	len = 0;
	t_redir *lst_redir;
	
	while (*tokens)
	{
		lst_redir = gc_alloc(sizeof(t_redir *), ALLOC);
		lst_redir = NULL;
		cmd_str = ft_prepare_cmd(tokens, &lst_redir, &len);
		t_cmd *cc = NULL;
		cc = ft_new_cmd(cmd_str, lst_redir, len);
		ft_add_back_cmd(lst_cmd, cc);
		i++;
	}
	return 0;
}
