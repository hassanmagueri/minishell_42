/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:18:39 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/18 22:11:06 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// void	ft_exit()
// {
	
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void exit_builtin() {
    exit(0);
}

int main()
{
    char command[MAX_COMMAND_LENGTH];

    while (1)
    {
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0)
            exit_builtin();
        else
            printf("Unknown command: %s\n", command);
    }

    return 0;
}
