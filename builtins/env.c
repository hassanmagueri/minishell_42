/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 05:02:31 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/16 14:42:28 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_lst_env(t_lst_env *lst)
{
	t_lst_env *cur;

	cur = lst;
	while (cur)
	{
		if (cur->value != NULL)
		{
			printf("%s", cur->key);
			printf("=%s\n", cur->value);	
		}
		cur = cur->next;
	}
}

int	ft_env(t_lst_env **lst,t_cmd *args)
{
	if (args->cmd[1] == NULL)
		print_lst_env(*lst);
	return (0);
}
