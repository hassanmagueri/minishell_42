/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:22:45 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/05 12:49:04 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_excut_cmd_line(t_lst_env *lst, t_cmd *args, t_data *pip)
{
	if (ft_strncmp(args->cmd[0], "cd", 3) == 0)
		ft_cd(lst, args);
	else if (ft_strncmp(args->cmd[0],"echo",5) == 0)
		ft_echo(args);
	else if (ft_strncmp(args->cmd[0], "env", 4) == 0)
		print_lst_env(lst);
	else if (ft_strncmp(args->cmd[0], "exit", 5) == 0)
		ft_exit(args);
	else if (ft_strncmp(args->cmd[0], "export", 7) == 0)
		ft_export(lst, args);
	else if (ft_strncmp(args->cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(args->cmd[0], "unset", 6) == 0)
		ft_unset(lst, args);
	return (0);
}
int	ft_check_buitin_cmd(t_cmd	*args)
{
	if ((ft_strncmp(args->cmd[0], "cd", 3) == 0)
		||(ft_strncmp(args->cmd[0],"echo",5) == 0)
		||(ft_strncmp(args->cmd[0], "env", 4) == 0)
		||(ft_strncmp(args->cmd[0], "exit", 4) == 0)
		||(ft_strncmp(args->cmd[0], "export", 7) == 0)
		||(ft_strncmp(args->cmd[0], "pwd", 4) == 0)
		||(ft_strncmp(args->cmd[0], "unset", 6) == 0))
		return (1);
	return (0);
}
