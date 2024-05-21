/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/21 12:36:39 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_cmd(t_cmd	*command,t_lst_env **lst,t_data *pip)
{
	t_cmd	*cur;
	int status;
	cur = command;
	int input_fd = -1;

	int	i = 0;
	pip->last = 0;
	while(cur->next)
	{
		if (i==0)
			pip->first = 1;
		else
			pip->first = 0;
		ft_excut_child(cur,pip,lst,&input_fd);
		cur = cur->next;
		i++;
	}
	pip->first = 0;
	pip->last = 1;
	ft_excut_child(cur,pip,lst,&input_fd);
	while (wait(&status) != -1)
		;
	if (WIFEXITED(status))
        cur->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
        cur->exit_status = WTERMSIG(status)+ 128;
    printf("status=%d\n", cur->exit_status);
}

void	ft_chech_excut_cmd(t_cmd	*command,t_lst_env **lst,t_data *pip)
{
	int i;
	i = 0;
	t_cmd	*cur;
	cur = command;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	if (i == 1 && ft_check_buitin_cmd(command)==1)
		ft_excut_cmd_line(lst,command,pip);
	else
		ft_lst_cmd(command,lst,pip);
}
