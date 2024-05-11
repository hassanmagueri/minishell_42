/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:52:28 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/08 16:30:41 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    handle_c_slash_ctrol(int signal)
{
    if (signal == SIGINT)
    {
        write(1,"\n",1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
     if (signal == SIGQUIT)
        rl_replace_line("", 0);
        // return ;
}

void    handle_slash_ctrol(int signal)
{
    printf(" ");
    return ;
}

int ft_signal_handeler(void)
{
    signal(SIGINT, handle_c_slash_ctrol);
    signal(SIGQUIT, handle_c_slash_ctrol);
    return (0);
}
