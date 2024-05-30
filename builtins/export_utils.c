/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:07:01 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/30 16:36:14 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_lst_export(t_lst_env *lst)
{
	t_lst_env	*cur;

	cur = lst;
	while (cur)
	{
		if (ft_strncmp(cur->key, "_", 2) == 0)
		{
			cur = cur->next;
			continue ;
		}
		printf("declare -x ");
		if (cur->value)
		{
			printf("%s", cur->key);
			printf("=\"%s\"\n", cur->value);
		}
		else
			printf("%s\n", cur->key);
		cur = cur->next;
	}
}

int	index_key(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '+' && str[i + 1] == c) || str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_check_lst_key(t_lst_env **lst, char *key)
{
	t_lst_env	*cur;

	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	ft_prasing_export(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1 || str[0] == '\0' || str[0] == '=')
		return (1);
	while (str[i] == '_')
		i++;
	while (str[i])
	{
		if (str[i] == '_')
			i++;
		else if (ft_isalnum(str[i]) != 1)
			return (1);
		else
			i++;
	}
	return (0);
}

void	ft_add_val(t_lst_env **lst, char *key, char *val)
{
	t_lst_env	*cur;

	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			if (cur->value == NULL)
				cur->value = ft_join_value_lst(cur->value, val, ALLOC_ENV);
			else
				cur->value = ft_strjoin(cur->value, val, ALLOC_ENV);
			break ;
		}
		cur = cur->next;
	}
}
