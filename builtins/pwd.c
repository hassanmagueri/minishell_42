/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:58:19 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/24 21:20:34 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_lst_env **lst)
{
	char cmd[1024];
	char *pwd;
	if (getcwd(cmd,sizeof(cmd)) != NULL)
	{
		ft_putendl_fd(cmd, 1);
		return(0);
	}
	else
	{
		pwd = ft_get_env_val(lst, "PWD");
		ft_putendl_fd(pwd, 1);
		return(0);
	}
	return (1);
}
