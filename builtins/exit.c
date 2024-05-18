/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:18:39 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/18 15:54:44 by ataoufik         ###   ########.fr       */
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
        if ((num > LLONG_MAX && sig == 1) || (num - 1 > LLONG_MAX && sig == -1))
            return (1); 
        else
            i++;
    }
    return (num);
}
int    ft_exit(t_cmd   *args)// % 256
{
    int i;
    long long int status;
    status = 0;
    i = 1;
    int r = 0;
    while(args->cmd[i])
    {
        if (ft_parsing_exit(args->cmd[i]) == 1 && r == 0)
        {
            printf("exit: %s: numeric argument required\n",args->cmd[i]);
             status = 2;
            r = 1;
        }
        i++;  
    }
    if ((i == 1 || i == 2) && r == 0)
    {
        ft_putendl_fd("exit", 1);
        if(ft_parsing_exit(args->cmd[i]) != 1)
            status = ft_parsing_exit(args->cmd[i]);
    }
    if (i>2 && r == 0)
    {
        ft_putendl_fd("exit: too many arguments", 2);
        status = 1;
        
    }
    exit(status);
    // return(status);
}

