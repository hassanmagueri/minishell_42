/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/21 11:45:52 by emagueri         ###   ########.fr       */
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

t_cmd	*ft_new_cmd(char **cmd, t_redir *redir)
{
	t_cmd *cmds;

	// cmds = malloc(sizeof(t_cmd));
	cmds = gc_alloc(sizeof(t_cmd), ALLOC);
	cmds->cmd = cmd;
	cmds->redir = redir;
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
	printf("len : %d\n", len);
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

int ft_is_this_arr(int *indexes, int len, int index)
{
	int i;
	i = 0;

	while (i < len)
	{
		if (indexes[i] == index)
			return (1);
		i++;
	}
	
	return (0);
}

int reset_cmd_arr(t_cmd *cmd_node, int *indexes, int len_indexes, int len_arr_str)
{
	char **new_str_arr;
	char **str_arr;
	int i;
	int i_count;

	i_count = 0;
	str_arr = cmd_node->cmd;
	i = 0;
	new_str_arr = gc_alloc(sizeof(char *) * (len_indexes + len_arr_str + 1), ALLOC);
	while (str_arr[i])
	{
		if (ft_is_this_arr(indexes, len_indexes, i))
		{
			i_count++;
			char **res = ft_split(str_arr[i], ' ', ALLOC);
			new_str_arr[i + i_count - 1] = res[0];
			new_str_arr[i + i_count] = res[1];
		}
		else
			new_str_arr[i + i_count] = str_arr[i];
		i++;
	}
	new_str_arr[i + i_count] = NULL;
	cmd_node->cmd = new_str_arr;
	return 0;
}

int ft_split_array(t_cmd **lst_cmd)
{
	t_cmd *cur;
	int i;
	char **str_arr;
	int *indexes;
	int len_indexes;

	cur = *lst_cmd;
	while (cur)
	{
		i = 0;
		len_indexes = 0;
		indexes = NULL;
		str_arr = cur->cmd;
		while (str_arr[i])
		{
			if (ft_strchr(str_arr[i], ' '))
				ft_add_int(&indexes, &len_indexes, i);
			i++;
		}
		if (len_indexes > 0)
			reset_cmd_arr(cur, indexes, len_indexes, i);
		cur = cur->next;
	}
	return 0;
}

char	**ft_delete_first_array(char **matrix)
{
	int		i;
	int		len;
	char	**new_matrix;

	len = 0;
	while (matrix[len])
		len++;
	new_matrix = gc_alloc(len * sizeof(char *), ALLOC);
	i = -1;
	while (++i < len)
	{
		new_matrix[i] = matrix[i + 1];
	}
	// new_matrix[i] = NULL;
	return (new_matrix);
}

int ft_cmd(t_cmd **lst_cmd, t__lst_token **tokens)
{
	char **cmd_str;
	int	i = 0;
	t_redir *lst_redir;
	
	while (*tokens)
	{
		lst_redir = gc_alloc(sizeof(t_redir *), ALLOC);
		lst_redir = NULL;
		cmd_str = ft_prepare_cmd(tokens, &lst_redir);
		while (ft_strncmp(cmd_str[0], "/", 1) == 0)
			cmd_str[0] = FLAG_HEREDOC;
		t_cmd *cc = NULL;
		cc = ft_new_cmd(cmd_str, lst_redir);
		ft_add_back_cmd(lst_cmd, cc);
		i++;
	}
	return 0;
}
