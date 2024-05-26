/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:58:19 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/26 17:18:01 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_lst_env **lst)
{
	char cmd[1024];
	getcwd(cmd,sizeof(cmd));
	ft_putendl_fd(cmd, 1);
	return(0);
}
