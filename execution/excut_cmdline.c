/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:22:45 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/18 20:18:12 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_excut_cmd_line(t_lst_env **lst, t_cmd *args, t_data *pip)
{
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
