/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:13:00 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/30 16:19:20 by ataoufik         ###   ########.fr       */
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
	if (i == 1)
	{
		if (ft_strncmp(args->cmd[0], "unset", 6) == 0)
			return ;
		if (ft_check_val(lst, "_") == 0)
			ft_change_value_lst(lst, "_", args->cmd[0]);
		else
			ft_lst_add_back_env(lst, ft_new_env("_", args->cmd[0]));
	}
	else
	{
		if (ft_check_val(lst, "_") == 0)
			ft_change_value_lst(lst, "_", NULL);
		else
			ft_lst_add_back_env(lst, ft_new_env("_", NULL));
	}
}
