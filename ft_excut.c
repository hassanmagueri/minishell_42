/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/23 23:24:00 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_arr(char **str)
{
	int i;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*find_path_executable(char **env_path, char *cmd)
{
	char	*str;
	char	*path;
	int		i;

	i = 0;
	str = NULL;
	path = NULL;
	if (access(cmd, X_OK) == 0 && access(cmd, F_OK) == 0)
		return (cmd);
	while (env_path[i])
	{
		str = ft_strjoin(env_path[i], "/");
		path = ft_strjoin(str, cmd);
		free(str);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}

void	ft_execute_command(char **env_path, char **str)
{
	char *command;

	command = find_path_executable(env_path, str[0]);
	if (command == NULL)
		printf("Invalid argument\n");
	execve(command, str, NULL);
	free_2d_arr(str);
	free(command);
}
// void process_child(char **cmd, t_redir *red, char **env_path,int *tub,int is_last)
// {
//     pid_t pid;

//     pid = fork();
//     if (pid == 0)
// 	{
//         if (is_last == 0)
// 		{
//             close(tub[0]);
//             dup2(tub[1], STDOUT_FILENO);
//             close(tub[1]);
//         }
//         ft_execute_command(env_path, cmd); 
//     } 
// 	else if (pid > 0)
// 	{
//         if (is_last == 0)
// 		{
//             close(tub[1]); 
//     	        dup2(tub[0], STDIN_FILENO);
//             close(tub[0]);
//         }
// 	}
// }
// void	process_child(char **cmd,t_redir	*red,char **env_path, int is_last)
// {
// 	int tub[2];
// 	pid_t pid;
	
// 	if (is_last==0)
// 	{
// 		if (pipe(tub) == -1)
// 			printf("error in pipe");	
// 	}
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(tub[0]);
// 		dup2(tub[1], STDOUT_FILENO);
// 		close(tub[1]);
// 		// if (red->redirection_type == APPEND || red->redirection_type == OUTPUT)
// 		// {
// 		// 	dup2(red->outfile,STDOUT_FILENO);
// 		// 	close(red->outfile);
// 		// }
// 		ft_execute_command(env_path,cmd);
// 	}
// 	else
// 	{
// 		close(tub[1]);
// 		dup2(tub[0], STDIN_FILENO);
// 		close(tub[0]);
// 	}
// }
void process_child(char **cmd,t_redir *redir,char **env_path,int *tub, int is_last)
{
    pid_t pid = fork();

    if (pid == 0)
	{
		// close(0);
        if (!is_last)
            dup2(tub[1], STDOUT_FILENO);
		// close(1);
        close(tub[0]);
		ft_execute_command(env_path,cmd);
    }
	else 
	{
        close(tub[1]);
		// close(1);
        if (!is_last)
            dup2(tub[0], STDIN_FILENO);
			// close(0);
		// wait(NULL);
    }
}
void ft_excut_cmd(char **cmd,t_redir *redir ,int *tub,char **env_path,int i)
{
	t_redir	*cur;
	cur = redir;
	// while(cur)
	// {
	// 	if (cur->redirection_type == INPUT)
	// 	{
	// 		cur->infile = open(cur->file_name, O_RDONLY);
	// 		dup2(cur->infile,STDIN_FILENO);
	// 		close(cur->infile);
	// 	}
	// 	else if (cur->redirection_type == OUTPUT)
	// 	{
	// 		cur->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_TRUNC, 0666);
	// 	}
	// 	else if (cur->redirection_type == HEARDOC)
	// 	{
	// 		// ft_here_doc(cur,pip);
	// 	}
	// 	else if (cur->redirection_type == APPEND)
	// 	{
	// 		cur->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
			
	// 	}
	// 	cur = cur->next;
	// }
	if (cmd != NULL)
		process_child(cmd,redir,env_path,tub,i);
}

void	ft_lst_cmd(t_cmd	*command, char **env_path)
{
	t_cmd	*cur;
	cur = command;
	int pipe_fd[2];
	int is_last = 0;
	while(cur)
	{
		if (cur->next)
		{
			if (pipe(pipe_fd) == -1)
			{
                perror("pipe");
                return;
            }
		}
		else
			is_last = 1;
		ft_excut_cmd(cur->cmd,cur->redir ,pipe_fd,env_path,is_last);
		cur = cur->next;
	}
	// ft_excut_cmd(cur->cmd,cur->redir ,env_path,1);
	while (wait(NULL) != -1)
		;
}
