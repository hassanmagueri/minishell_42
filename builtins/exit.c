/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:18:39 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/01 17:07:41 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_parsing_exit(char *str)
{
    int i;
    int sig = 1;
    unsigned long long num;
    i = 0;
    num = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sig *= -1;
        i++;
    }
    while(str[i])
    {
        if (ft_isdigit(str[i]) != 1)
            return (1);
        num = num * 10 + str[i] - 48;
        if (num == LLONG_MAX + 1 && sig == -1)
            i++;
        else if (num > LLONG_MAX)
            return (1);
        else
            i++;
    }
    return (0);
}
int    ft_exit(t_cmd   *args)
{
    int i;
    i = 1;
    int r = 0;
    while(args->cmd[i])
    {
        if (ft_parsing_exit(args->cmd[i]) == 1 && r==0)
        {
            printf("exit: %s: numeric argument required\n",args->cmd[i]);
            r = 1;
        }
        i++;  
    }
    if ((i == 1 || i == 2)&& r==0)
    {
        ft_putendl_fd("exit", 1);
        exit(0);
    }
    if (i>2 && r == 0)
        ft_putendl_fd("exit: too many arguments", 2);

    return(1);
}

