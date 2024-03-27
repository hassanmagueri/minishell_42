/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:58:19 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/20 17:38:50 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd,sizeof(cwd)) != NULL)
    {
        printf("%s\n",cwd);
        exit(0);
    }
    else
    {
        perror("error");
        exit(1);
    }
}
