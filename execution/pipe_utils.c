/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:49:22 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/30 20:16:38 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_default_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	ft_dup_close_infile(int infile)
{
	if (infile != 0)
	{
		if (infile < 0)
		{
			perror("infile");
			exit(1);
		}
		else
		{
			dup2(infile, STDIN_FILENO);
			close(infile);
		}
	}
	return (0);
}
