/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:22:45 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/21 12:46:44 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_excut_cmd_line(t_lst_env **lst, t_cmd *args, t_data *pip)
{
	pip->infile = 0;
	pip->outfile = 1;
	int infile = dup(0);
	int outfile = dup(1);
	ft_redirection(args,pip);
	if (pip->infile != 0)
	{
		perror("infile");
		return (1);
	}
	if (pip->outfile != 1)
    {
		if (pip->outfile < 0)
		{
            perror("outfile");
            return 1;
		}
			dup2(pip->outfile,1);
			close(pip->outfile);
	}
	
	if (ft_strncmp(args->cmd[0], "cd", 3) == 0)
		args->exit_status = ft_cd(lst, args);
	else if (ft_strncmp(args->cmd[0],"echo",5) == 0)
		args->exit_status = ft_echo(args);
	else if (ft_strncmp(args->cmd[0], "env", 4) == 0)
		args->exit_status = ft_env(lst,args); //
	else if (ft_strncmp(args->cmd[0], "exit", 5) == 0)
		args->exit_status = ft_exit(args); //
	else if (ft_strncmp(args->cmd[0], "export", 7) == 0)
		args->exit_status = ft_export(lst, args); //
	else if (ft_strncmp(args->cmd[0], "pwd", 4) == 0)
		args->exit_status = ft_pwd();//
	else if (ft_strncmp(args->cmd[0], "unset", 6) == 0)
		args->exit_status = ft_unset(lst, args); //
	
	if (dup2(infile, 0) == -1)
    {
        perror("dup2 infile");
        return 1;
    }
    close(infile);

    if (dup2(outfile, 1) == -1)
    {
        perror("dup2 outfile");
        return 1;
    }
    close(outfile);

	return (0);
}

int	ft_cmd_builtin_child(t_lst_env **lst, t_cmd *args, t_data *pip)
{
	if (ft_strncmp(args->cmd[0], "cd", 3) == 0)
		exit(ft_cd(lst, args));
	else if (ft_strncmp(args->cmd[0],"echo",5) == 0)
		exit(ft_echo(args));
	else if (ft_strncmp(args->cmd[0], "env", 4) == 0)
		exit(ft_env(lst,args));
	else if (ft_strncmp(args->cmd[0], "exit", 5) == 0)
		exit(ft_exit(args));
	else if (ft_strncmp(args->cmd[0], "export", 7) == 0)
		exit(ft_export(lst, args));
	else if (ft_strncmp(args->cmd[0], "pwd", 4) == 0)
		exit(ft_pwd());
	else if (ft_strncmp(args->cmd[0], "unset", 6) == 0)
		exit(ft_unset(lst, args));
	return (0);
}
int	ft_check_buitin_cmd(t_cmd	*args)
{
	if ((ft_strncmp(args->cmd[0], "cd", 3) == 0) ||(ft_strncmp(args->cmd[0],"echo",5) == 0) ||(ft_strncmp(args->cmd[0], "env", 4) == 0) ||(ft_strncmp(args->cmd[0], "exit", 4) == 0) ||(ft_strncmp(args->cmd[0], "export", 7) == 0) ||(ft_strncmp(args->cmd[0], "pwd", 4) == 0) ||(ft_strncmp(args->cmd[0], "unset", 6) == 0))
		return (1);
	return (0);
}
