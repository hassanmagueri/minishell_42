/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 16:29:00 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_redirection(t_cmd	*cmd, t_data *pip)
{
	t_redir *cur;

	cur = cmd->redir;
	int i = 0;              
	while(cur)
	{
		if (cur->redirection_type == OUTPUT)
		{
			if (pip->outfile != 1)
				close(pip->outfile);
			if (cur->file_name == NULL)
			{
				ft_putendl_fd("ambiguous redirect ",2);
				exit (1);
			}
			if (pip->infile >= 0)
				pip->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);

		}
		else if (cur->redirection_type == APPEND)
		{
			if (pip->outfile != 1)
				close(pip->outfile);
			if (cur->file_name == NULL)
			{
				ft_putendl_fd("ambiguous redirect ",2);
				exit (1);
			}
			if (pip->infile >= 0)
				pip->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_APPEND, 0666);

		}
		else if (cur->redirection_type == INPUT)
		{
			if (pip->infile != 0)
				close(pip->infile);
			if (cur->file_name == NULL)
			{
				ft_putendl_fd("ambiguous redirect ",2);
				exit (1);
			}
			pip->infile = open(cur->file_name, O_RDONLY);
		}
		else if (cur->redirection_type == HEARDOC)
		{
			if (pip->infile != 0)
				close(pip->infile);
			pip->infile = ft_atoi(cur->file_name);
		}
		i++;
		cur = cur->next;
	}
}
