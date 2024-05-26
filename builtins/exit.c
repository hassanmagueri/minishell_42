/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:18:39 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/26 19:37:51 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_parsing_exit(char *str)
{
    int i;
    i = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    while(str[i])
    {
        if (ft_isdigit(str[i]) != 1)
            return (1);
        i++;
    }
    return (0);
}

long long int ft_number_exit(char *str)
{
    int i;
    int sig = 1;
    unsigned long long num;
    i = 0;
    num = 0;
     if (str == NULL)
    {
        printf("exit: numeric argument required\n");
        return (255);
    }

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sig *= -1;
        i++;
    }
    while(str[i])
    {
        num = num * 10 + str[i] - 48;
        if (num != 0 && ((num > LLONG_MAX && sig == 1) || (num - 1 > LLONG_MAX && sig == -1)))
        {
            ft_putstr_fd("exit: ",2);
            ft_putstr_fd(str,2);
            ft_putendl_fd(": numeric argument required", 2);
            return (2);
        }
        else
            i++;
    }
    return (num * sig);
}

int    ft_exit(t_cmd   *args,int *ex_state)
{
    int i = 0;
    int r = 0;
    int status;
    char **str;
    status = 0;
    ft_putendl_fd("exit", 1);
    if (args->cmd[1]== NULL)
        exit(*ex_state);
      str =   ft_split_space_tab(args->cmd[1], ALLOC);
    // str = ft_split(args->cmd[1],' ',ALLOC);// spac tab...
    while (str[i])
        i++;
    if (i > 1)
    {
        ft_putendl_fd("exit: too many arguments", 2);
        return (1);
    }  
    else if (ft_parsing_exit(str[0]) == 0 && i ==1 &&args->len== 1)
        exit(ft_number_exit(str[0]) % 256);
    i = 1;
    while(args->cmd[i])
    {
        if (i >= 2 && ft_parsing_exit(args->cmd[1]) == 0)
        {
            ft_putendl_fd("exit: too many arguments", 2);
            return (1);
        }
        if (ft_parsing_exit(args->cmd[i]) == 1)
        {
            ft_putstr_fd("exit: ",2);
            ft_putstr_fd(args->cmd[i],2);
            ft_putendl_fd(": numeric argument required", 2);
            status = 255;
            r = 1;
            break;
        }
        i++;
    }
    if (i == 2 && r == 0)
        status = ft_number_exit(args->cmd[1]) % 256;
    exit(status);

    return (0);
}
