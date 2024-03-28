/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 16:31:18 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/16 16:34:30 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <string.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

char **get_input(char *input)
{
    char **command;

    command = malloc(8 * sizeof(char *));
    if (command == NULL)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    char *delimiter = " \t\n";
    char *token = strtok(input, delimiter);
    int i = 0;

    while (token != NULL)
    {
        command[i++] = token;
        token = strtok(NULL, delimiter);
    }
    command[i] = NULL;
    return command;
}
int main(){
    char **command;
    char *input;
    pid_t child_pid;
    int stat_loc;

    while (1)
    {
        input = readline("unixsh> ");
        command = get_input(input);

        child_pid = fork();
        if (child_pid == 0)
        {
            execvp(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        }
        else
            waitpid(child_pid, &stat_loc, WUNTRACED);
        free(input);
        free(command);
    }

    return 0;
}