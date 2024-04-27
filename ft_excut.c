/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/27 18:09:10 by ataoufik         ###   ########.fr       */
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
void	ft_excut_child(t_cmd *cmd,char **env_path,int is_last,int is_first,int *input_fd)
{
	int tub[2];
	if (is_last!= 1)
		pipe(tub);
	pid_t pid = fork();
	if (pid == 0)
	{
		
        if (is_first == 1)
		{
            dup2(tub[1], STDOUT_FILENO);
            close(tub[0]);
            close(tub[1]);
        }
		else if (is_first == 0 && is_last == 0)
		{
           dup2(*input_fd, STDIN_FILENO);
            dup2(tub[1], STDOUT_FILENO);
            close(*input_fd);
            close(tub[0]);
            close(tub[1]);
        }
		else if (is_last == 1)
		{
  			dup2(*input_fd, STDIN_FILENO);
            close(*input_fd);
        }
		
		ft_execute_command(env_path,cmd->cmd);
	}
	else
	{
		if (is_first==1)
		{
			close(tub[1]);
			*input_fd = tub[0];
		}
		else if (is_first==0 && is_last==0)
		{
			close(*input_fd);
			close(tub[1]);
			*input_fd = tub[0];			
		}
		else if (is_last == 1)
		{
			close(*input_fd);
		}
	}	
}
void	ft_lst_cmd(t_cmd	*command, char **env_path)
{
	t_cmd	*cur;
	cur = command;
	int input_fd = -1;

	int	i = 0;
	while(cur->next)
	{
		if (i==0)
			ft_excut_child(cur,env_path,0,1,&input_fd);
		else
			ft_excut_child(cur,env_path,0,0,&input_fd);
		cur = cur->next;
		i++;
	}
	ft_excut_child(cur,env_path,1,0,&input_fd);
	while (wait(NULL) != -1)
		;
}
