/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/18 15:25:58 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_redirection(t_cmd	*cmd, t_data *pip)
{
	t_redir *cur;

	cur = cmd->redir;
	while(cur)
	{
		if (cur->redirection_type == OUTPUT)
		{
			if (pip->outfile != -1)
				close(pip->outfile);
			pip->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			printf("trunc = %d\n",pip->outfile);

		}
		else if (cur->redirection_type == APPEND)
		{
			if (pip->outfile != -1)
				close(pip->outfile);
			pip->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_APPEND, 0666);
			printf("append = %d\n",pip->outfile);


		}
		else if (cur->redirection_type == INPUT)
		{
			if (pip->infile != 0)
				close(pip->infile);
			pip->infile = open(cur->file_name, O_RDONLY);
			// printf("%d\n",pip->infile);
		}
		else if (cur->redirection_type == HEARDOC)
		{
			//here_doc
		}
		cur = cur->next;
	}
}
