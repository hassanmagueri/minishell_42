/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:13:00 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/31 18:52:24 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_val(t_lst_env **lst_env, char *key)
{
	t_lst_env	*cur;

	cur = *lst_env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}

void	ft_add_last_cmd(t_lst_env **lst, t_cmd *args, int i)
{
	int	j;

	j = 0;
	if (i == 0 || args->cmd[0] == NULL)
	{
		if (ft_check_val(lst, "_") == 0)
			ft_change_value_lst(lst, "_", NULL);
		else
			ft_lst_add_back_env(lst, ft_new_env("_", NULL));
	}
	else
	{
		while (args->cmd[j])
			j++;
		j--;
		if (ft_check_val(lst, "_") == 0)
			ft_change_value_lst(lst, "_", args->cmd[j]);
		else
			ft_lst_add_back_env(lst, ft_new_env("_", args->cmd[j]));
	}
}
