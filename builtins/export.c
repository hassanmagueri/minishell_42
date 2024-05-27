/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:07:30 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 16:32:39 by ataoufik         ###   ########.fr       */
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

int	error_msg_export(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

// void	ft_key_and_value(char *value ,char *key,int len ,char *str)
// {
// 	if (len != -1)
// 	{
// 		key = ft_substr(str, 0, len, ALLOC_ENV);
// 		value = ft_strchr(str, '=') + 1;
// 	}
// 	else
// 	{
// 		key = ft_strdup(str, ALLOC_ENV);
// 		value = ft_strdup(NULL, ALLOC_ENV);
// 	}
// }

int	ft_export(t_lst_env **lst_env, t_cmd *str)
{
	int		len;
	int		status;
	char	*value;
	char	*key;
	int		i;

	status = 0;
	i = 1;
	// if (*lst_env== NULL)
	// 	return 1;
	if (str->cmd[i] == NULL)
		print_lst_order_alpha(lst_env);
	else
	{
		while (str->cmd[i])
		{
			if (str->cmd[i] == NULL)
			{
				i++;
				continue ;
			}
			len = index_key(str->cmd[i], '=');
			if (len != -1)
			{
				key = ft_substr(str->cmd[i], 0, len, ALLOC_ENV);
				value = ft_strdup(ft_strchr(str->cmd[i], '=') + 1,ALLOC_ENV);
			}
			else
			{
				key = ft_strdup(str->cmd[i], ALLOC_ENV);
				value = ft_strdup(NULL, ALLOC_ENV);
			}
			// ft_key_and_value(value ,key,len ,str->cmd[i]);
			if (ft_prasing_export(key) == 1)
			{
				status = error_msg_export(str->cmd[i++]);
				continue ;
			}
			if (ft_check_lst_key(lst_env, key) == 1)
			{
				if (len != -1 && str->cmd[i][len] == '+')
					ft_add_val(lst_env, key, value);
				else
					ft_change_val(lst_env, key, value);
			}
			else
				ft_lst_add_back_env(lst_env, ft_new_env(key, value));
			i++;
		}
	}
	return (status);
}
