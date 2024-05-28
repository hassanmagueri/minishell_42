/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/28 20:29:31 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_num_node(t_cmd *args)
{
	t_cmd	*cur;
	int		i;

	i = 0;
	cur = args;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

void	ft_excut_all_cmd(t_cmd *cmd, t_data *pip, t_lst_env **lst, int *ex_s)
{
	t_cmd	*cur;
	int		i;

	i = 0;
	cur = cmd;
	pip->pid_index = 0;
	pip->last = 0;
	while (cur->next)
	{
		if (i == 0)
			pip->first = 1;
		else
			pip->first = 0;
		ft_excut_child(cur, pip, lst, ex_s);
		cur = cur->next;
		i++;
	}
	pip->first = 0;
	pip->last = 1;
	ft_excut_child(cur, pip, lst, ex_s);
}

void	ft_lst_cmd(t_cmd	*command, t_lst_env **lst, t_data *pip, int *ex_s)
{
	struct termios	state;
	int				status;
	int				i;

	i = 0;
	tcgetattr(STDOUT_FILENO, &state);
	pip->input_fd = -1;
	pip->num_cmds = ft_num_node(command);
	pip->pids = gc_alloc(pip->num_cmds * sizeof(pid_t), ALLOC_ENV);
	if (!pip->pids)
		exit(EXIT_FAILURE);
	ft_excut_all_cmd(command, pip, lst, ex_s);
	while (i < pip->num_cmds)
		waitpid(pip->pids[i++], &status, 0);
	if (WIFEXITED(status))
		*ex_s = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		*ex_s = WTERMSIG(status) + 128;
		if (*ex_s == 131)
			printf("Quit: 3\n");
		else
			printf("\n");
	}
	tcsetattr(STDOUT_FILENO, TCSANOW, &state);
}

void	ft_check_cmd(t_cmd *command, t_lst_env **lst, t_data *pip, int *ex_s)
{
	t_cmd	*cur;
	int		i;

	i = 0;
	cur = command;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	if (i == 1 && ft_check_buitin_cmd(command) == 1)
		ft_excut_cmd_line(lst, command, pip, ex_s);
	else
		ft_lst_cmd(command, lst, pip, ex_s);
}
