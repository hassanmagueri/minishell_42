/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:18:39 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/29 19:49:40 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_exit(t_cmd   *args)
{
    int i;
    i = 0;
    while(args->cmd[i])
        i++;
    if (i > 2)
        ft_putendl_fd("exit: too many arguments", 2);

    // else if(i == 1)
    // {
    //     i = 0;
    //     while (args->cmd[1][i])
    //     {
    //         printf("ddddddddd\n"); 
    //         if (args->cmd[1][i]&&(args->cmd[1][i] >='0' && args->cmd[1][i] <='9'))
    //             i++;
    //         else if (args->cmd[1][i]&&(args->cmd[1][i] =='+' || args->cmd[1][i] =='-'))
    //         {
    //             if ((args->cmd[1][i +1]&& args->cmd[1][i + 1] =='+' || args->cmd[1][i + 1] =='-'))
    //                 printf("exit: %s: numeric argument required",args->cmd[1]);
    //             i++;
    //         }
    //         else
    //             printf("exit: %s: numeric argument required",args->cmd[1]);

    //         i++;
    //     }
    // }
    else
    {
    
        ft_putendl_fd("exit", 1);
        exit(0);
    }
    return(1);
}

