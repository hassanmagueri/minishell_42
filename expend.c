/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/01 21:25:32 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		is_var(char *str, int *index)
{
	int i;

	i = *index;
	if (ft_isdigit(str[i]))
		i++;
	else
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
	*index = i;
	return (0);
}



int ft_expand(t__lst_token **lst_token, t_lst_env **lst_env)
{
	t__lst_token	*cur;
	char			*str;
	// t_lst_env       *var;

	cur = *lst_token;
	while (cur)
	{
		if (cur->type == VAR)
			cur->str = ft_get_env_val(lst_env, cur->str + 1);
		else if(cur->type == DOUB_Q)
		{
			char *res = cur->str;
			int i = 0;
			int start = 0;
			while (res[i])
			{
				if (res[i] == '$')
				{
					if(res[i + 1] == '$')
					{
						
					}
				}
				i++;
			}
		}
		cur = cur->next;
	}
	return 1;
}
