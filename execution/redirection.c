/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/01 16:35:22 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_redirection(t_cmd	*cmd, t_data *pip)
{
	t_redir *cur;

	cur = cmd->redir;
	while(cur)
	{
		if (cur->redirection_type == 4)
		{
			if (pip->outfile!= -1)
				close(pip->outfile);
			pip->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		}
		else if (cur->redirection_type == 1)
		{
			if (pip->outfile!= -1)
				close(pip->outfile);
			pip->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		else if (cur->redirection_type == 3)
		{
			if (pip->infile != -1)
				close(pip->infile);
			pip->infile = open(cur->file_name, O_RDONLY);
		}
		else if (cur->redirection_type == 3)
		{
			//here_doc
		}
		cur = cur->next;
	}
}
