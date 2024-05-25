/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:36:44 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/24 22:26:07 by emagueri         ###   ########.fr       */
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
			str = ft_get_env_val(lst_env, next->str + 1);
			if (next->type == VAR && ft_is_wsp_middle(str))
				return (print_error("ambiguous redirect"));
		}
		cur = cur->next;
	}
	return 0;
}

int ft_parsing(t__lst_token **lst_token, t_lst_env **lst_env, t_cmd **lst_cmd, int exit_status)
{
	
	int n = generate_errors(lst_token);
	ft_trim(lst_token);
	if (n)
	{
		ft_heredoc(lst_token, lst_env);
		gc_alloc(0, FREE);
		return 258;
	}
	if (ft_ambiguous_main(lst_token, lst_env))
		return 1;
	ft_expand(lst_token, lst_env, exit_status);// exit state
	if (ft_join(lst_token))
		return 1;
	ft_heredoc(lst_token, lst_env);
	// print__lst_tokens(*lst_token);
	ft_cmd(lst_cmd, lst_token);
	// print_lst_cmd(lst_cmd);
	return 0;
}
