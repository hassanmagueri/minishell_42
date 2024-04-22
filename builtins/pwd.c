/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 15:58:19 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/21 14:42:21 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char cmd[1024];
	if (getcwd(cmd,sizeof(cmd)) != NULL)
	{
		ft_putendl_fd(cmd, 1);
		return(0);
	}
	return (1);

}
// int main()
// {
// 	ft_pwd();
// }
