/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excut_cmdline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:22:45 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/29 09:33:48 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_excut_cmd_line(t_lst_env *lst, t_cmd *args, t_data *pip)
{
	if (ft_strncmp(args->cmd[0], "cd", ft_strlen(args->cmd[0])) == 0)
		ft_cd(lst, args);
	// else if (ft_strncmp(args->cmd[0],"echo",ft_strlen(args->cmd[0])) == 0)
	else if (ft_strncmp(args->cmd[0], "env", ft_strlen(args->cmd[0])) == 0)
		print_lst_env(lst);
	else if (ft_strncmp(args->cmd[0], "exit", ft_strlen(args->cmd[0])) == 0)
		ft_exit(args);
	else if (ft_strncmp(args->cmd[0], "export", ft_strlen(args->cmd[0])) == 0)
		ft_export(lst, args);
	else if (ft_strncmp(args->cmd[0], "pwd", ft_strlen(args->cmd[0])) == 0)
		ft_pwd();
	else if (ft_strncmp(args->cmd[0], "unset", ft_strlen(args->cmd[0])) == 0)
		ft_unset(&lst, args);
	else
		ft_execute_command(pip, args->cmd);
	return (0);
}