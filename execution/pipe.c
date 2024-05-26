/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:33:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/26 17:41:57 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_excut_child(t_cmd *args,t_data *pip,t_lst_env **lst,int *input_fd,int *ex_state)
{
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	if (pip->last!= 1)
		pipe(pip->tub);
	pid_t pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		pip->infile = 0;
		pip->outfile = 1;
		ft_redirection(args,pip);
		if (pip->infile != 0)
		{
			if(pip->infile < 0)
			{
				perror("infile");
                // printf("no  such file or directory");
				exit(1);
			}
			else
			{	
				dup2(pip->infile,STDIN_FILENO);
				close(pip->infile);
			}
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
		if (pip->outfile != 1)
        {
            if (pip->outfile < 0)
            {
				ft_putendl_fd("No such file or directory",2);
                exit(1);
            }
            dup2(pip->outfile, STDOUT_FILENO);
			if (ft_check_buitin_cmd(args) == 1)
				ft_cmd_builtin_child(lst,args,pip,ex_state);
			else
				ft_execute_command(pip,lst,args->cmd);
            close(pip->outfile);
        }
		else
		{
			if (ft_check_buitin_cmd(args) == 1)
				ft_cmd_builtin_child(lst,args,pip,ex_state);
			else
				ft_execute_command(pip,lst,args->cmd);
		}
        // fanction->pp
		exit(EXIT_SUCCESS);
	}
	else
	{
		pip->pids[pip->pid_index++] = pid;
		if (pip->first != 1)
			close(*input_fd);
		if (pip->last != 1)
		{
			close(pip->tub[1]);
			*input_fd = pip->tub[0];
			
		}
	}	
}
