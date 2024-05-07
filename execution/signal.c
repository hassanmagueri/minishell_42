/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:52:28 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/05 17:52:01 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    handle_c_ctrol(int signal)
{
    write(1,"\n",1);
    rl_replace_line(" ", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    handle_slash_ctrol(int signal)
{
    printf(" ");
    return ;
}

int ft_signal_handeler(void)
{
    if (signal(SIGINT, handle_c_ctrol) == SIG_ERR)
        return 1;
    else if (signal(SIGQUIT, handle_slash_ctrol) == SIG_ERR)
        return 1;
    return (0);
}
