/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/17 11:54:58 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<minishell.h>
char	*find_path_executable(t_data *pip, char *cmd)
{
	char	*str;
	char	*path;
	int		i;

	i = 0;
	str = NULL;
	path = NULL;
	if (access(cmd, X_OK) == 0 && access(cmd, F_OK) == 0)
		return (cmd);
	while (pip->env_path[i])
	{
		str = ft_strjoin(pip->env_path[i], "/");
		path = ft_strjoin(str, cmd);
		free(str);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}

void	ft_execute_command(t_data *pip, char *str)
{
	char	**cmd;
	char *command;

	cmd = ft_split_space_tab(str);
	if (cmd == NULL)
		printf("Invalid argument");
	command = find_path_executable(pip, cmd[0]);
	if (command == NULL)
		printf("Invalid argument");
	execve(command, cmd, NULL);
	free_2d_arr(cmd);
	free(command);
}

void	process_child(t_data *pip, char *str)
{
	char	*command;

	command = NULL;
	if (pipe(pip->tub) == -1)
		printf("error in pipe");
	pip->pid = fork();
	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[1]);
		ft_execute_command(pip, str);
	}
	else
	{
		close(pip->tub[1]);
		dup2(pip->tub[0], STDIN_FILENO);
		close(pip->tub[0]);
	}
}

void	process_child_last(t_data *pip,char *str)
{
	char	*command;

	command = NULL;
	pip->pid = fork();
	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[1]);
		// ft_open_outfile(pip, i);
		dup2(pip->outfile, STDOUT_FILENO);
		close(pip->outfile);
		ft_execute_command(pip, str);
	}
	else
	{
		close(pip->tub[1]);
		dup2(pip->tub[0], STDIN_FILENO);
		close(pip->tub[0]);
	}
}
int ft_cmdpip(t_data **pip, char *str)
{
	  
}
void	ft_lst_cmd(t_cmd	**command, t_data	**pip)
{
	t_cmd   *cur;

	cur = *command;
	while(cur)
	{
		if (!(ft_cmdpip(pip,cur->cmd)))
			return(0);
		cur = cur->next;
	}
}