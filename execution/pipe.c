/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:33:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/28 22:54:31 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_output_handling(t_data *pip, t_lst_env **lst, t_cmd *args, int *ex_s)
{
	if (pip->outfile != 1)
	{
		if (pip->outfile < 0)
		{
			ft_putendl_fd("No such file or directory", 2);
			exit(1);
		}
		dup2(pip->outfile, STDOUT_FILENO);
		if (ft_check_buitin_cmd(args) == 1)
			ft_cmd_bui_child(lst, args, pip, ex_s);
		else
			ft_execute_command(pip, lst, args->cmd);
		close(pip->outfile);
	}
	else
	{
		if (ft_check_buitin_cmd(args) == 1)
			ft_cmd_bui_child(lst, args, pip, ex_s);
		else
			ft_execute_command(pip, lst, args->cmd);
	}
	exit(EXIT_SUCCESS);
}

void	ft_setup_pipeline(t_data *pip)
{
	if (pip->first != 1)
	{
		dup2(pip->input_fd, STDIN_FILENO);
		close(pip->input_fd);
	}
	if (pip->last != 1)
	{
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[0]);
		close(pip->tub[1]);
	}
}

void	ft_update_pipeline_fds(t_data *pip)
{
	if (pip->first != 1)
		close(pip->input_fd);
	if (pip->last != 1)
	{
		close(pip->tub[1]);
		pip->input_fd = pip->tub[0];
	}
}

void	ft_excut_child(t_cmd *args, t_data *pip, t_lst_env **lst, int *ex_state)
{
	pid_t	pid;

	ft_signal_ignore();
	if (pip->last != 1)
		pipe(pip->tub);
	pid = fork();
	if (pid == 0)
	{
		ft_default_signal();
		pip->infile = 0;
		pip->outfile = 1;
		ft_redirection(args, pip);
		ft_setup_pipeline(pip);
		ft_dup_close_infile(pip->infile);
		ft_output_handling(pip, lst, args, ex_state);
	}
	else
	{
		pip->pids[pip->pid_index++] = pid;
		ft_update_pipeline_fds(pip);
	}
}
