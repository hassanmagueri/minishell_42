/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:22:45 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/29 23:16:52 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	excut_builtins(t_lst_env **lst, t_cmd *args, int *ex_state)
{
	if (ft_strncmp(args->cmd[0], "cd", 3) == 0)
		*ex_state = ft_cd(lst, args);
	else if (ft_strncmp(args->cmd[0], "echo", 5) == 0)
		*ex_state = ft_echo(args);
	else if (ft_strncmp(args->cmd[0], "env", 4) == 0)
		*ex_state = ft_env(lst, args);
	else if (ft_strncmp(args->cmd[0], "exit", 5) == 0)
		*ex_state = ft_exit(args, ex_state);
	else if (ft_strncmp(args->cmd[0], "export", 7) == 0)
		*ex_state = ft_export(lst, args);
	else if (ft_strncmp(args->cmd[0], "pwd", 4) == 0)
		*ex_state = ft_pwd();
	else if (ft_strncmp(args->cmd[0], "unset", 6) == 0)
		*ex_state = ft_unset(lst, args);
}

int	ft_excut_cmd_line(t_lst_env **lst, t_cmd *args, t_data *pip, int *ex_state)
{
	int	infile;
	int	outfile;

	pip->outfile = 1;
	pip->infile = 0;
	infile = dup(0);
	outfile = dup(1);
	ft_redirection(args, pip);
	if (pip->infile != 0)
	{
		perror("infile");
		close(pip->infile);
		*ex_state = 1;
		return (1);
	}
	if (pip->outfile != 1)
	{
		if (ft_dup_and_close_outfile(pip->outfile, 1) == 1)
			return (1);
	}
	excut_builtins(lst, args, ex_state);
	ft_dup_and_close(infile, 0);
	ft_dup_and_close(outfile, 1);
	return (0);
}

int	ft_cmd_bui_child(t_lst_env **lst, t_cmd *args, t_data *pip, int *ex_state)
{
	(void) pip;
	signal(SIGINT, SIG_DFL);
	if (ft_strncmp(args->cmd[0], "cd", 3) == 0)
		exit(ft_cd(lst, args));
	else if (ft_strncmp(args->cmd[0], "echo", 5) == 0)
		exit(ft_echo(args));
	else if (ft_strncmp(args->cmd[0], "env", 4) == 0)
		exit(ft_env(lst, args));
	else if (ft_strncmp(args->cmd[0], "exit", 5) == 0)
		exit(ft_exit(args, ex_state));
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
	if ((ft_strncmp(args->cmd[0], "cd", 3) == 0)
		|| (ft_strncmp(args->cmd[0], "echo", 5) == 0)
		|| (ft_strncmp(args->cmd[0], "env", 4) == 0)
		|| (ft_strncmp(args->cmd[0], "exit", 4) == 0)
		|| (ft_strncmp(args->cmd[0], "export", 7) == 0)
		|| (ft_strncmp(args->cmd[0], "pwd", 4) == 0)
		|| (ft_strncmp(args->cmd[0], "unset", 6) == 0))
		return (1);
	return (0);
}
