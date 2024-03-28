/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:04:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/21 01:18:11 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_redirect_input(char *str)
{
    int i;
    int p;

    i = 0;
    p = 1;
    while (str[i])
    {
        while (str[i] && str[i] == ' ' || str[i] == '\t')
            i++;
        if (str[i]== '<')
        {
            i++;
            while (str[i] && str[i] == ' ' || str[i] == '\t')
                i++;
            if (str[i] == '#')
                return (1);
        }
        i++;
    }
    return (0);
}
int ft_redirect_output(char *str);