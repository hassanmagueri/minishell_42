/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 01:32:15 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_first_cmd(t__lst_token **lst_token)
{
	t__lst_token	*cur;
	char			*res;

	res = "";
	cur = *lst_token;
	while (cur
		&& cur->type != WORD && cur->type != DOUB_Q && cur->type != SING_Q)
		cur = cur->next;
	while (cur
		&& (cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q))
	{
		res = ft_strjoin(res, cur->str, ALLOC);
		cur = cur->next;
	}
	return (res);
}

int	ft_is_endl_with_with_space(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_is_with_spaces(str[len - 1]))
		return (1);
	return (0);
}

int	ft_is_strong_word_befor(t__lst_token **lst_token, t__lst_token *last)
{
	t__lst_token	*cur;

	cur = *lst_token;
	while (cur
		&& cur->type != WORD && cur->type != DOUB_Q && cur->type != SING_Q)
		cur = cur->next;
	while (cur
		&& (cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q))
		cur = cur->next;
	if (cur->type == VAR)
		return (1);
	while (cur != last)
	{
		if (((cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q)
				&& cur->str[0] != '\0'))
			return (1);
		cur = cur->next;
	}
	return (0);
}

t__lst_token	*ft_add_wsp_before(t__lst_token **cur_pointer)
{
	t__lst_token	*tmp;
	t__lst_token	*cur;

	cur = *cur_pointer;
	tmp = ft_new_token(cur->str, cur->type);
	cur->str = "";
	cur->type = WSP;
	cur->next = tmp;
	cur = cur->next;
	*cur_pointer = cur;
	return (cur);
}

void	ft_add_wsp_middle(t__lst_token **cur_pointer)
{
	char			*str;
	char			**value_twod_array;
	t__lst_token	*cur;
	int				i;

	i = 0;
	cur = *cur_pointer;
	str = cur->str;
	value_twod_array = ft_split_ws(cur->str, ALLOC);
	cur->str = value_twod_array[i++];
	while (value_twod_array[i])
	{
		if (value_twod_array[i] != 0)
		{
			cur->next = ft_new_token("", WSP);
			cur = cur->next;
		}
		cur->next = ft_new_token(value_twod_array[i], WORD);
		cur = cur->next;
		i++;
	}
	*cur_pointer = cur;
}
