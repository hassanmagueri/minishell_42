    /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:59:44 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/22 02:02:57 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// token -->  "< > << >> |" gir mandatory li gadi ndiro
int ft_chack_cara(char *str ,char c)
{
    int i;
    int n = 0;
    i = 0;
    while(str[i])
    {
        if (str[i] == c)
            return (1);
        i++;
    }
    return (0);
}
int ft_number_of_token(char *str)
{
    int i = 0;
    int n = 0;
    while(str[i])
    {
        if (ft_chack_cara("<>|",str[i]) == 1)
        {
            n++;
            if (ft_chack_cara("<>|",str[i + 1]) == 1)
                i++;
        }
        i++;        
    }
    return (n);
}

char **ft_find_token(char *str)
{
    char **arry;
    int i = 0;

    int n = ft_number_of_token(str);
    arry = malloc(sizeof(char *) * (n + 1));
    if (!arry)
        return (NULL);
    while (str[i])
    {

    }
    return arry;
}


int main ()
{
    char *str;
    char **str1;
    int i = 0;

    str = " < dwdwdweqf | WQ | ef << ";
    str1 = ft_find_token(str);
    while(str1[i])
        printf("|    %s     |\n",str1[i++]);
    printf("token = %d\n",ft_number_of_token(str));
    return (0);
}