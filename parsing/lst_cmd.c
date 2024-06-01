/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 10:43:06 by emagueri          #+#    #+#             */
/*   Updated: 2024/06/01 09:54:13 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_redirs(t_redir **redirs, t_lst_token **cur_pointer,
			t_type type)
{
	char			*file_name;
	t_lst_token		*cur;

	cur = ft_next_token(cur_pointer);
	file_name = "";
	while (cur && (cur->type == EXIT_STATUS || cur->type == VAR
			|| cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q))
	{
		if (cur->str == NULL)
		{
			cur = cur->next;
			if (!(cur && cur->type == VAR))
				file_name = NULL;
			continue ;
		}
		file_name = ft_strjoin(file_name, cur->str, ALLOC);
		cur = cur->next;
		if (cur && cur->type == WSP && cur->str[0] == 0 && cur->next
			&& cur->next->type == VAR && cur->next->str)
		{
			(1) && (file_name = NULL, cur = cur->next);
		}
	}
	ft_add_back_redir(redirs, ft_new_redir(file_name, type));
	*cur_pointer = cur;
}

char	**ft_prepare_cmd_loop(t_lst_token	**cur_pointer,
			t_redir **lst_redir, int len)
{
	int				i;
	char			**cmd;
	t_lst_token		*cur;

	i = 0;
	cmd = gc_alloc(sizeof(char *) * (len + 1), ALLOC);
	cur = *cur_pointer;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == WSP || cur->str == NULL)
		{
			cur = cur->next;
			continue ;
		}
		else if (cur->type <= OUTPUT)
		{
			ft_handle_redirs(lst_redir, &cur, cur->type);
			continue ;
		}
		cmd[i++] = cur->str;
		cur = cur->next;
	}
	cmd[i] = NULL;
	*cur_pointer = cur;
	return (cmd);
}

char	**ft_prepare_cmd(t_lst_token **tokens, t_redir **lst_redir)
{
	char			**cmd;
	t_lst_token		*cur;
	int				len;

	len = ft_len_cmd_part(tokens);
	cur = *tokens;
	cmd = ft_prepare_cmd_loop(&cur, lst_redir, len);
	if (cur)
		*tokens = cur->next;
	else
		*tokens = NULL;
	if ((*tokens) && (*tokens)->type == PIPE)
		*tokens = (*tokens)->next;
	return (cmd);
}

void	print_lst_cmd(t_cmd **cmd)
{
	t_cmd	*cur;
	int		i;
	t_redir	*cur_red;

	cur = *cmd;
	while (cur)
	{
		i = 0;
		printf("[CMD]:");
		while (cur->cmd && cur->cmd[i])
			printf("[%s]", cur->cmd[i++]);
		cur_red = cur->redir;
		printf("\n[FILES]:");
		while (cur_red)
		{
			printf("{%s}", cur_red->file_name);
			cur_red = cur_red->next;
		}
		printf("\n");
		printf("\n");
		cur = cur->next;
	}
}

int	ft_cmd(t_cmd **lst_cmd, t_lst_token **tokens)
{
	char	**cmd_str;
	t_cmd	*cc;
	t_redir	*lst_redir;

	while (*tokens)
	{
		lst_redir = gc_alloc(sizeof(t_redir *), ALLOC);
		lst_redir = NULL;
		cmd_str = ft_prepare_cmd(tokens, &lst_redir);
		cc = NULL;
		cc = ft_new_cmd(cmd_str, lst_redir);
		ft_add_back_cmd(lst_cmd, cc);
	}
	return (0);
}
