/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/18 10:35:47 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

void	ft_execute_command(t_data *pip, char **str)
{
	char *command;

	command = find_path_executable(pip, str[0]);
	if (command == NULL)
		printf("Invalid argument");
	execve(command, str, NULL);
	free_2d_arr(str);
	free(command);
}

void	process_child(t_redir	*red,t_data *pip)//sing last pipe
{
	char	*command;
	int tub[2];
	pid_t pid;
	command = NULL;
	if (red->sig != /*last command*/)
	{
		if (pipe(tub) == -1)
			printf("error in pipe");	
	}
	pid = fork();
	if (pid == 0)
	{
		close(tub[0]);
		dup2(tub[1], STDOUT_FILENO);
		close(tub[1]);
		if (/*if type redriction out or herdoc_out*/)
		{
			dup2(red->outfile,STDOUT_FILENO);
			close(red->outfile);
		}
		ft_execute_command(pip,red->cmd);
	}
	else
	{
		close(tub[1]);
		dup2(tub[0], STDIN_FILENO);
		close(tub[0]);
	}
}

void ft_excut_cmd(t_redir	*red,t_data *pip,int i)
{
	t_redir	*cur;
	cur = red;
	while(cur)
	{
		if (/*infile*/)
		{
			cur->infile = open(cur->str, O_RDONLY);
			dup2(cur->infile,STDIN_FILENO);
			close(cur->infile);
		}
		else if (/*outfile*/)
		{
			cur->outfile = open(cur->str,O_CREAT | O_WRONLY | O_TRUNC, 0666);
			
		}
		else
			process_child(cur,pip);
			
		cur = cur->next;
	}
	
}

void	ft_lst_cmd(t_cmd	*command,t_data *pip)
{
	t_cmd	*cur;
	cur = command;
	while(cur->next)
	{
		ft_excut_cmd(cur->redir,pip,0);
		cur = cur->next;
	}
	ft_excut_cmd(cur->redir,pip,1);
}
