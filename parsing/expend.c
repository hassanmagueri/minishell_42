/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/31 16:57:51 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_expand_vars(t_lst_token **lst_token, t_lst_env **lst_env,
		t_lst_token **cur_pointer, t_lst_token *prev)
{
	t_lst_token		*cur;
	t_lst_token		*next;
	char			*first_cmd;
	char			*str;

	(1) && (first_cmd = ft_first_cmd(lst_token), cur = *cur_pointer);
	cur->str = ft_get_env_val(lst_env, cur->str + 1);
	next = cur->next;
	if (ft_strncmp(first_cmd, "export", ft_strlen(first_cmd) + 1) == 0)
		return (*cur_pointer = next, 1);
	if (cur->str != NULL)
	{
		if (ft_is_with_spaces(cur->str[0]) && prev && (prev->type == VAR
				|| (ft_is_strong_word_befor(lst_token, cur->next))))
			ft_add_wsp_before(&cur);
		str = cur->str;
		ft_add_wsp_middle(&cur);
		if (next && (ft_is_endl_with_with_space(str)) && next->type != WSP)
		{
			cur->next = ft_new_token("", WSP);
			cur = cur->next;
		}
		cur->next = next;
	}
	return (*cur_pointer = cur, 0);
}

char	*ft_expand_in_doub_q(t_lst_env **lst_env, char *str, int exit_state)
{
	char	*res;
	int		i;

	i = 0;
	res = "";
	while (i < ft_strlen(str))
	{
		if (str[i] == '$' && str[i + 1] == '$')
			(1) && (i += 2, res = ft_strjoin(res, "$$", ALLOC));
		if (str[i] == '$' && str[i + 1] == '?')
		{
			i += 2;
			res = ft_strjoin(res, ft_itoa(exit_state, ALLOC), ALLOC);
		}
		else if (str[i] == '$'
			&& str[i + 1] != 0 && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			res = ft_strjoin(res, ft_handle_var(lst_env, str + i, &i), ALLOC);
		}
		else
			res = ft_handle_simple_string(str + i, res, &i);
	}
	return (res);
}

void	ft_skip_delimiter(t_lst_token **cur_pointer)
{
	t_lst_token	*cur;

	cur = *cur_pointer;
	cur = cur->next;
	if (cur && cur->type == WSP)
		cur = cur->next;
	while (cur && cur->type != WSP)
		cur = cur->next;
	*cur_pointer = cur;
}

int	ft_expand(t_lst_token **lst_token, t_lst_env **lst_env, int *exit_state)
{
	t_lst_token	*cur;
	t_lst_token	*prev;

	prev = NULL;
	cur = *lst_token;
	while (cur)
	{
		if (cur->type == HEARDOC)
		{
			ft_skip_delimiter(&cur);
			continue ;
		}
		if (cur->type == EXIT_STATUS)
			cur->str = ft_itoa(*exit_state, ALLOC);
		else if (cur->type == VAR
			&& ft_expand_vars(lst_token, lst_env, &cur, prev))
			continue ;
		else if (cur->type == DOUB_Q)
			cur->str = ft_expand_in_doub_q(lst_env, cur->str, *exit_state);
		prev = cur;
		cur = cur->next;
	}
	return (1);
}
