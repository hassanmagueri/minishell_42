/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:17:13 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/25 12:39:42 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_child(t_lst_env *lst, t_cmd *args, t_data *pip)
{
	if (pipe(pip->tub) == -1)
    {
        pritnf("error pipeline");
        return ;
    }
	pip->pid = fork();

	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[1]);
		ft_excut_cmd_line(lst,args,pip);
	}
	else
	{
		close(pip->tub[1]);
		dup2(pip->tub[0], STDIN_FILENO);
		close(pip->tub[0]);
	}
}


void	process_child_last(t_lst_env *lst, t_cmd *args, t_data *pip)
{
	pip->pid = fork();

	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[1]);
		// ft_open_outfile(pip, pip->sig);
		// dup2(pip->outfile, STDOUT_FILENO);
		// close(pip->outfile);
		ft_excut_cmd_line(lst,args,pip);
	}
	else
	{
		close(pip->tub[1]);
		dup2(pip->tub[0], STDIN_FILENO);
		close(pip->tub[0]);
	}
}

void  ft_open_redir(t_lst_env *lst, t_cmd *args,t_data *pip,int i)
{
	t_redir	*cur;
	cur = args->redir;
	while(cur)
	{
		if (cur->redirection_type == INPUT)
		{
			pip->infile = open(cur->file_name, O_RDONLY);
			dup2(pip->infile,STDIN_FILENO);
			close(pip->infile);
		}
		else if (cur->redirection_type == OUTPUT)
		{
			pip->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_TRUNC, 0666);
		}
		else if (cur->redirection_type == HEARDOC)
		{
			// ft_here_doc(cur,pip);
		}
		else if (cur->redirection_type == APPEND)
		{
			pip->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
			
		}
		cur = cur->next;
	}
	if (args->cmd != NULL)
    {
        if (i == 1)
		    process_child(lst,args,pip);
        else
           process_child_last(lst,args,pip);
    }
}
void	ft_lst_cmd(t_lst_env *lst, t_cmd *args,t_data *pip)
{
	t_cmd	*cur;
	cur = args;

	while(cur->next)
	{
        ft_open_redir(lst,args,pip,1);
		cur = cur->next;
	}
    ft_open_redir(lst,args,pip,0);
	while (wait(NULL) != -1)
		;
}