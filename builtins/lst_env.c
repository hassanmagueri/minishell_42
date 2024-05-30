/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:02:31 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 16:35:52 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst_env	*ft_get_env(t_lst_env **lst_env, char *key)
{
	t_lst_env	*cur;

	if (lst_env == NULL)
		return (NULL);
	cur = *lst_env;
	while (cur)
	{
		if (ft_strncmp(key, cur->key, ft_strlen(cur->key) + 1) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	ft_lst_add_back_env(t_lst_env **lst_env, t_lst_env *node_env)
{
	if (lst_env == NULL || ft_get_env(lst_env, node_env->key) != NULL)
		return (-1);
	if (*lst_env == NULL)
		*lst_env = node_env;
	else
		ft_lst_env_last(*lst_env)->next = node_env;
	return (0);
}

int	index_of(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	handle_env_entry(t_lst_env **lst, char *str)
{
	char	*key;
	char	*value;
	int		len;

	len = index_of(str, '=');
	if (len == -1)
		return (-1);
	if (ft_strncmp(str, "OLDPWD", len) == 0)
		value = NULL;
	else
		value = ft_strdup(ft_strchr(str, '=') + 1, ALLOC_ENV);
	key = ft_substr(str, 0, len, ALLOC_ENV);
	ft_lst_add_back_env(lst, ft_new_env(key, value));
	return (0);
}

int	init_env(t_lst_env **lst, char **env)
{
	int	i;

	i = 0;
	if (*env == NULL)
		return (ft_lst_add_back_env(lst, ft_new_env("OLDPWD", NULL)), 1);
	while (env[i])
	{
		if (ft_strncmp(env[i], "_", 2) == 0)
		{
			i++;
			continue ;
		}
		if (handle_env_entry(lst, env[i]) == -1)
			return (-1);
		i++;
	}
	return (1);
}
