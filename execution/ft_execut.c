/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/24 15:32:07 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_cmd(t_cmd	*command,t_lst_env **lst,t_data *pip)
{
	t_cmd	*cur;
	struct termios state;
	tcgetattr(STDOUT_FILENO,&state);
	int status;
	cur = command;
	int input_fd = -1;
	int	i = 0;
	int num_cmds = 0;
    while (cur) {
        num_cmds++;
        cur = cur->next;
    }
	pip->pids = malloc(num_cmds * sizeof(pid_t));
    if (!pip->pids)
        exit(EXIT_FAILURE);

	pip->pid_index = 0;
    pip->num_cmds = num_cmds;
	cur = command;
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
	i = 0;
	while (i < pip->num_cmds)
	{
        waitpid(pip->pids[i], &status, 0);
		
		if (WIFEXITED(status))
			command->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			command->exit_status = WTERMSIG(status) + 128;
			if (command->exit_status == 131)
				printf("Quit: 3\n");
			else
				printf("\n");
		}
		i++;
	}
	tcsetattr(STDOUT_FILENO,TCSANOW,&state);
	// free -> pids 
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
