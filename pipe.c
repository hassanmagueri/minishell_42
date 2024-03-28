/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 00:16:54 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/28 01:48:14 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	inist_pipe(t_pipe *pip, char *evm[])
{
	char	*default_path;

	// if (!evm || !*evm)
	// {
	// 	default_path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:";
	// 	pip->env_path = ft_split (default_path, ':');
	// 	if (!pip->env_path)
	// 		ft_error("Invalid argument");
	// 	return ;
	// }
	while (evm && *evm && ft_strncmp(*evm, "PATH=", 5) != 0)
		evm++;
	if (*evm == NULL)
		ft_error("Path not found");
	*evm += 5;
	pip->env_path = ft_split (*evm, ':');
	if (!pip->env_path)
		ft_error("Invalid argument");
}


void	process_child(t_pipe *pip, int i)
{
	char	*command;

	command = NULL;
	if (pipe(pip->tub) == -1)
		ft_messg_error("error in pipe");
	pip->pid = fork();
	if (pip->pid == -1)
		ft_messg_error("Error in fork");
	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		if (dup2(pip->tub[1], STDOUT_FILENO) == -1)
			ft_messg_error("Error in dup2");
		close(pip->tub[1]);
		ft_execute_command(pip, i, command);
	}
	else
	{
		close(pip->tub[1]);
		if (dup2(pip->tub[0], STDIN_FILENO) == -1)
			ft_messg_error("Error in dup2");
		close(pip->tub[0]);
	}
}
void	process_child_last(t_pipe *pip)
{
	char	*command;

	command = NULL;
	pip->pid = fork();
	if (pip->pid == -1)
		ft_messg_error("Error in fork");
	if (pip->pid == 0)
	{
		close(pip->tub[0]);
		dup2(pip->tub[1], STDOUT_FILENO);
		close(pip->tub[1]);
		ft_open_outfile(pip, pip->sig);// open_modes if ('>') O_TRUNC | O_CREAT | O_RDWR 
		// else if (">>") O_APPEND | O_CREAT | O_RDWR 
		// else par default stdout
		dup2(pip->outfile, STDOUT_FILENO);
		close(pip->outfile);
		// ft_execute_command(pip, pip->i, command);
	}
	else
	{
		close(pip->tub[1]);
		dup2(pip->tub[0], STDIN_FILENO);
		close(pip->tub[0]);
	}
}

void	ft_execute_command(t_pipe *pip, int i, char *command)
{
	char	**cmd;

	cmd = ft_split_space_tab(pip->args[i]);
	if (cmd == NULL)
		ft_error("Invalid argument");
	command = find_path_executable_b(pip, cmd[0]);
	if (command == NULL)
		ft_error("Invalid argument");
	execve(command, cmd, NULL);
	free_2d_arr(cmd);
	free(command);
}


void	ft_here_doc(t_pipe *pip)
{
	int		fds[2];
	char	*str;

	if (pipe(fds) == -1)
		ft_messg_error("error in pipe");
	pip->args[2] = ft_strjoin(pip->args[2], "\n");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (str == NULL || (ft_strncmp(pip->args[2], str, ft_strlen(pip->args[2])) != 1))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fds[1]);
		free(str);
	}
	close (fds[1]);
	if (dup2(fds[0], STDIN_FILENO) == -1)
		ft_messg_error("Error in dup2");
	close (fds[0]);
}



char	*find_path_executable_b(t_pipe *pip, char *cmd)
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

void	ft_pipe(char *arv[], char *evm[])
{
	t_pipe	pip;

	inist_pipe(&pip, evm);

	// case < 
	// pip.infile = open(pip.args[1], O_RDONLY);
	// dup2(pip.infile, STDIN_FILENO);
	// close(pip.infile);
	//<<       ft_here_doc(t_pipe *pip)

	// input ----> process
	
	// process_child(&pip, pip.i);

}