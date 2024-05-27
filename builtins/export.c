/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:07:30 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 18:23:39 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lst_order_alpha(t_lst_env **lst)
{
	t_lst_env	*cur;
	char		*temp;
	char		*temp1;

	if (*lst == NULL)
		ft_lst_add_back_env(lst, ft_new_env("OLDPWD", NULL));
	cur = *lst;
	while (cur->next != NULL)
	{
		if (ft_strcmp(cur->key, cur->next->key) > 0)
		{
			temp = cur->key;
			temp1 = cur->value;
			cur->key = cur->next->key;
			cur->value = cur->next->value;
			cur->next->key = temp;
			cur->next->value = temp1;
			cur = *lst;
		}
		else
			cur = cur->next;
	}
	cur = *lst;
	print_lst_export(cur);
}

void	ft_change_val(t_lst_env **lst, char *key, char *value)
{
	t_lst_env	*cur;

	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			if (value != NULL)
				cur->value = value;
			break ;
		}
		cur = cur->next;
	}
}

void	ft_update_lst(t_lst_env **lst_env, char *key, char *value, char *str)
{
	int	len;

	len = index_key(str, '=');
	if (ft_check_lst_key(lst_env, key) == 1)
	{
		if (len != -1 && str[len] == '+')
			ft_add_val(lst_env, key, value);
		else
			ft_change_val(lst_env, key, value);
	}
	else
		ft_lst_add_back_env(lst_env, ft_new_env(key, value));
}

int	ft_export(t_lst_env **lst_env, t_cmd *str)
{
	int		status;
	char	*value;
	char	*key;
	int		i;

	i = 1;
	status = 0;
	if (str->cmd[i] == NULL)
		print_lst_order_alpha(lst_env);
	else
	{
		while (str->cmd[i])
		{
			key = ft_key(key, index_key(str->cmd[i], '='), str->cmd[i]);
			value = ft_value(value, index_key(str->cmd[i], '='), str->cmd[i]);
			if (ft_prasing_export(key) == 1)
			{
				status = error_msg_export(str->cmd[i++]);
				continue ;
			}
			ft_update_lst(lst_env, key, value, str->cmd[i]);
			i++;
		}
	}
	return (status);
}
