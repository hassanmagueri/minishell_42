/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/03 18:08:30 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_redirection(t_cmd	*cmd, t_data *pip)
{
	t_redir *cur;

	cur = cmd->redir;
	while(cur)
	{
		// printf("%d\n",cur->redirection_type);
		if (cur->redirection_type == OUTPUT)
		{
			if (pip->outfile!= -1)
				close(pip->outfile);
			pip->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
		}
		else if (cur->redirection_type == APPEND)
		{
			if (pip->outfile!= -1)
				close(pip->outfile);
			pip->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_APPEND, 0666);
		}
		else if (cur->redirection_type == INPUT)
		{
			if (pip->infile != -1)
				close(pip->infile);
			pip->infile = open(cur->file_name, O_RDONLY);
		}
		else if (cur->redirection_type == HEARDOC)
		{
			//here_doc
		}
		cur = cur->next;
	}
}
