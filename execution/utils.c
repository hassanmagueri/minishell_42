/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:28:54 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/30 16:47:22 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dup_and_close(int file, int i)
{
	if (dup2(file, i) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(file);
	return (0);
}

int	ft_dup_and_close_outfile(int outfile, int i)
{
	(void)i;
	if (outfile < 0)
	{
		perror("outfile");
		return (1);
	}
	dup2(outfile, 1);
	close(outfile);
	return (0);
}
