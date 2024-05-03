/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:52:28 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/03 17:15:29 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    handle_c_ctrol(int signal)
{
    write(1,"\n",1);
    rl_on_new_line();
}
void    handle_d_ctrol(int signal)
{
    exit(0);
}
void    handle_slash_ctrol(int signal)
{
    
}

int ft_signal_handeler(void)
{
    if (signal(SIGINT, handle_c_ctrol) == SIG_ERR) {
        perror("Error setting signal handler");
        return 1;
    }
    else if (signal(SIGINT, handle_slash_ctrol) == SIG_ERR) {
        perror("Error setting signal handler");
        return 1;
    }
    else if (signal(SIGINT,handle_d_ctrol) == SIG_ERR) {
        perror("Error setting signal handler");
        return 1;
    }
    return (0);
}