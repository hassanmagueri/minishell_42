/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:42:31 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/23 16:45:53 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parsing_unset(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0])==1 || str[0]=='\0' || str[0] == '=')
		return (1);
	while(str[i]=='_')
		i++;
	while(str[i])
    {
		if (str[i]=='_')
			i++;
		else if (ft_isalnum(str[i])!=1)
			return (1);
        else
			i++;
    }
	return (0);
}

int ft_unset(t_lst_env **lst, t_cmd *args)
{
    t_lst_env   *cur;
    int status = 0;
    t_lst_env   *prev;
    int i;

    i = 1;
    while (args->cmd[i] != NULL)
    {
        cur = *lst;
        if (cur->next == NULL &&ft_strncmp(cur->key,args->cmd[i], ft_strlen(args->cmd[i])) == 0)
        {
            (*lst) = NULL;
            return (0);
        }
        prev = NULL;
        if (ft_parsing_unset(args->cmd[i]) != 0)
        {
            printf("unset: `%s': not a valid identifier\n",args->cmd[i]);
            status = 1;
            i++;
            continue;
        }
        while (cur != NULL)
        {
            if (ft_strncmp(cur->key,args->cmd[i], ft_strlen(args->cmd[i])) == 0)
            {
                if (prev == NULL)
                    (*lst) = cur->next;
                else
                    prev->next = cur->next;
                    break;
            }
            prev = cur;
            cur=cur->next;
        }
        i++;
    }
    return (status);
}
