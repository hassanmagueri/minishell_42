/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/08 14:52:53 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_lst_redir(t_redir *redir);

t_redir	*ft_new_redir(char *file_name, t_type redirection_type)
{
	t_redir *cmds;

	cmds = malloc(sizeof(t_redir));
	cmds->file_name = file_name;
	printf("new redir name %s\n", file_name);
	// printf("new redir type %d\n", redirection_type);
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

t_cmd	*ft_new_cmd(char **cmd, t_redir *redir, int *ignore_white_spaces)
{
	t_cmd *cmds;

	cmds = malloc(sizeof(t_cmd));
	cmds->cmd = cmd;
	cmds->redir = redir;
	cmds->ignore_white_spaces = ignore_white_spaces;
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

char	**ft_prepare_cmd(t__lst_token **tokens, t_redir **redirs, int **ignore_white_spaces)
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
	*ignore_white_spaces = malloc(sizeof(int) * (len + 1));
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
			t_type type;
			type = cur->type;
			cur = cur->next;
			if (cur && cur->type == SPACE)
				cur = cur->next;
			ft_add_back_redir(redirs, ft_new_redir(cur->str, type));
			if (cur)
				cur = cur->next;
			continue;
		}
		(*ignore_white_spaces)[i] = 1;
		if (cur->type == DOUB_Q)
			(*ignore_white_spaces)[i] = 0;
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
		while (cur->cmd[i])
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
	res = malloc(((*len) + 1) * sizeof(int));
	while (i < *len)
	{
		res[i] = arr[i];
		i++;
	}
	res[i] = n;
	(*len) += 1;
	free(arr);
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
	new_str_arr = malloc(sizeof(char *) * (len_indexes + len_arr_str + 1));
	while (str_arr[i])
	{
		if (ft_is_this_arr(indexes, len_indexes, i))
		{
			i_count++;
			char **res = ft_split(str_arr[i], ' ');
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
		if (str_arr && ft_strchr(str_arr[i], ' '))
			ft_add_int(&indexes, &len_indexes, i);
		while (str_arr[i])
			i++;
		if (len_indexes > 0)
			reset_cmd_arr(cur, indexes, len_indexes, i);
		cur = cur->next;
	}
	cur = *lst_cmd;
	while (cur)
	{
		i = 0;
		while (cur->cmd[i])
		{
			printf("i = {%d}\n", i);
			printf("cur->ignore_white_spaces[%d] = %d\n", i, cur->ignore_white_spaces[i]);
			if ((ft_strncmp("echo", cur->cmd[0], ft_strlen("echo") + 1) == 0 && cur->ignore_white_spaces[i]) || i != 0)
			{
				printf("it should ignore withe spaces \n");
				cur->cmd[i] = ft_strtrim(cur->cmd[i], " \t\n\v\r\f");
			}
			i++;
		}
		cur = cur->next;
	}
	return 0;
}

int ft_cmd(t_cmd **lst_cmd, t__lst_token **tokens, char **env_path)
{
	char **cmd_str;
	int	i = 0;
	t_redir *lst_redir;
	int *ignore_white_spaces;

	while (*tokens)
	{
		
		lst_redir = malloc(sizeof(t_redir *));
		lst_redir = NULL;
		cmd_str = ft_prepare_cmd(tokens, &lst_redir, &ignore_white_spaces);
		t_cmd *cc = NULL;
		cc = ft_new_cmd(cmd_str, lst_redir, ignore_white_spaces);
		ft_add_back_cmd(lst_cmd, cc);
		// if (ft_check_buitin_cmd(cc) == 0 && find_path_executable(env_path, cmd_str[0]) == NULL)
		// 	return 0;
			// printf(ANSI_COLOR_RED"%s : command not found\n"ANSI_COLOR_RESET, cmd_str[0]);
		print_lst_redir(cc->redir);
		i++;
	}
	print_lst_cmd(lst_cmd);
	ft_split_array(lst_cmd);
	return 0;
}
