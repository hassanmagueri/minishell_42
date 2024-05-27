/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:36:44 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/27 16:39:53 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_trim(t__lst_token **lst_token)
{
	t__lst_token *cur;

	cur = *lst_token;
	while (cur)
	{
		if (cur->type == DOUB_Q)
			cur->str = ft_strtrim(cur->str, "\"", ALLOC);
		else if (cur->type == SING_Q)
			cur->str = ft_strtrim(cur->str, "\'", ALLOC);
		cur = cur->next;
	}
	return 1;
}

int	ft_is_wsp_middle(char *str)
{
	int	i;
	int len;

	if (str == NULL)
		return 0;
	i = 0;
	while (str[i] && ft_is_with_spaces(str[i]))
		i++;
	len = ft_strlen(str) - 1;
	while (len >= 0 && ft_is_with_spaces(str[len]))
		len--;
	while (i < len)
	{
		if (ft_is_with_spaces(str[i]))
			return 1;
		i++;
	}
	return (0);
}

char	*ft_join_seq_vars(t__lst_token **lst, t_lst_env **lst_env)
{
	t__lst_token *cur;
	char *res;
	char *val;

	res = "";
	cur = *lst;
	while (cur && cur->type == VAR)
	{
		val = ft_get_env_val(lst_env, cur->str + 1);
		if (val)
			res = ft_strjoin(res, val, ALLOC);
		cur = cur->next;
	}
	*lst = cur;
	return res;
}

int ft_skip_this_part(t__lst_token **lst_token, t__lst_token **cur_node)
{
	t__lst_token *prev_part;
	t__lst_token *cur;
	t__lst_token *prev;

	prev_part = *lst_token;
	prev = NULL;
	cur = *lst_token;
	while (cur)
	{
		
		if (cur->type == PIPE)
			prev_part = cur;
		if (cur == *cur_node)
			break;
		prev = cur;
		cur = cur->next;
	}
	if (prev_part == *lst_token)
		*lst_token = ft_get_next_token_by_type(lst_token, PIPE);
	else
	{
		prev_part->next = ft_get_next_token_by_type(&cur, PIPE); // !!!!!!
		// prev->next->next = NULL;
	}
	return 1;
}

int ft_ambiguous_main(t__lst_token **lst_token, t_lst_env **lst_env)
{
	t__lst_token	*cur;
	t__lst_token	*next;
	char			*str;

	cur = *lst_token;
	while (cur)
	{
		next = cur->next;
		if (next && next->type == WSP)
			next = next->next;
		if (cur->type == OUTPUT && next)
		{
			// str = ft_get_env_val(lst_env, next->str + 1);
			str = ft_join_seq_vars(&next, lst_env);
			// if (next->type == VAR && ft_is_wsp_middle(str))
			if (ft_is_wsp_middle(str))
			{
				ft_skip_this_part(lst_token, &cur);
				print_error("ambiguous redirect");
				// return (print_error("ambiguous redirect"));
			}
		}
		cur = cur->next;
	}
	return 0;
}

int ft_parsing(t__lst_token **lst_token, t_lst_env **lst_env, t_cmd **lst_cmd, int *exit_status)
{
	
	int n = generate_errors(lst_token);
	ft_trim(lst_token);
	if (n)
	{
		ft_heredoc(lst_token, lst_env);
		gc_alloc(0, FREE);
		*exit_status = 258;
		return 258;
	}
	// print__lst_tokens(*lst_token);
	ft_expand(lst_token, lst_env, exit_status);// exit state
	ft_join(lst_token);
	ft_heredoc(lst_token, lst_env);
	// print__lst_tokens(*lst_token);
	ft_cmd(lst_cmd, lst_token);
	// print_lst_cmd(lst_cmd);
	return 0;
}
