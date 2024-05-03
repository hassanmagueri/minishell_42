/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:33:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/01 16:43:12 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_excut_child(t_cmd *args,t_data *pip,t_lst_env *lst,int *input_fd)
{
	if (pip->last!= 1)
		pipe(pip->tub);
	pid_t pid = fork();
	if (pid == 0)
	{
		ft_redirection(args,pip);
        // 
		if (pip->infile > 2)
		{
			dup2(pip->infile,STDIN_FILENO);
			close(pip->infile);
		}
		
		if (pip->outfile>2 && pip->last!=1)
		{
			dup2(pip->outfile,pip->tub[1]);
			close(pip->outfile);
		}
		else
		{
			dup2(pip->outfile,STDOUT_FILENO);
			close(pip->outfile);
		}
        // fanction->redirection 
        //
		if (pip->first!=1)
		{
  			dup2(*input_fd, STDIN_FILENO);
            close(*input_fd);
        }
		if (pip->last!=1)
		{
            dup2(pip->tub[1], STDOUT_FILENO);
            close(pip->tub[0]);
            close(pip->tub[1]);
        }
        // fanction->pp
		if (ft_check_buitin_cmd(args) == 1)
		{
			ft_excut_cmd_line(lst,args,pip);
			exit(0);
		}
		else
			ft_execute_command(pip, args->cmd);
	}
	else
	{
		if (pip->first != 1)
			close(*input_fd);
		if (pip->last != 1)
		{
			close(pip->tub[1]);
			*input_fd = pip->tub[0];
		}
	}	
}
