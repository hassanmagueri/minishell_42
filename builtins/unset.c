/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:42:31 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 12:08:02 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_msg_unset(char *str)
{
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

int	ft_parsing_unset(char *str)
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

void	ft_unset_node(t_lst_env **lst, t_lst_env *cur, t_lst_env *prev, char *s)
{
	while (cur != NULL)
	{
		if (ft_strncmp(cur->key, s, ft_strlen(s)) == 0)
		{
			if (prev == NULL)
				(*lst) = cur->next;
			else
				prev->next = cur->next;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
}

int	ft_unset(t_lst_env **lst, t_cmd *args)
{
	t_lst_env	*cur;
	t_lst_env	*prev;
	int			status;
	int			i;

	i = 1;
	status = 0;
	while (args->cmd[i] != NULL)
	{
		cur = *lst;
		if (cur->next == NULL && ft_strncmp(cur->key, args->cmd[i], ft_strlen(args->cmd[i])) == 0)
		{
			(*lst) = NULL;
			return (0);
		}
		prev = NULL;
		if (ft_parsing_unset(args->cmd[i]) != 0)
		{
			status = error_msg_unset(args->cmd[i++]);
			continue ;
		}
		ft_unset_node(lst, cur, prev, args->cmd[i]);
		i++;
	}
	return (status);
}
