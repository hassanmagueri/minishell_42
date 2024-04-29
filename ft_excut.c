/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_excut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:18:33 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/29 10:00:21 by ataoufik         ###   ########.fr       */
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

void	ft_execute_command(t_data *pip,char **cmd)
{
	char *command;

	command = find_path_executable(pip->env_path, cmd[0]);
	// int i = 0;
	// while(pip->env_path[i])
	//  	printf("%s\n",pip->env_path[i++]);
	if (command == NULL)
		printf("Invalid argument\n");
	execve(command, cmd, NULL);
	free_2d_arr(cmd);
	free(command);
}

void	ft_redirection(t_cmd	*cmd, t_data *pip)
{
	t_redir *cur;
	int outfile;
	int infile;

	outfile = -1;
	infile = -1;
	cur = cmd->redir;
	while(cur)
	{
		if (cur->redirection_type == 4)
		{
			pip->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0666);
			dup2(outfile,pip->outfile);
			close(outfile);
		}
		else if (cur->redirection_type == 0)
		{
			outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(outfile,pip->outfile);
			close(outfile);
		}
		else if (cur->redirection_type == 2)
		{
			infile = open(cur->file_name,O_RDONLY, 0666);
			dup2(infile,pip->infile);
			close(infile);
		}
		else if (cur->redirection_type == 1)
		{
			infile = open(cur->file_name,O_CREAT | O_WRONLY | O_APPEND, 0666);
			dup2(infile,pip->infile);
			close(infile);
		}
		cur = cur->next;
	}
}

// ft_excut_child(cur,pip,lst,&input_fd);
void	ft_excut_child(t_cmd *args,t_data *pip,t_lst_env *lst,int *input_fd)
{
	if (pip->last!= 1)
		pipe(pip->tub);
	pid_t pid = fork();
	if (pid == 0)
	{
		ft_redirection(args,pip);
		// printf("pip->outfile  %d\n",pip->outfile);
		// printf("pip->infile   %d\n",pip->infile);
		if (pip->infile)
		{
			dup2(pip->infile,0);
			close(pip->infile);
			
		}
		if (pip->outfile)
		{
			dup2(pip->outfile,1);
			close(pip->outfile);
			// printf("pip->outfile  %d\n",pip->outfile);
		}
			
        if (pip->first == 1)
		{
            dup2(pip->tub[1], STDOUT_FILENO);
            close(pip->tub[0]);
            close(pip->tub[1]);
        }
		else if (pip->first == 0 && pip->last == 0)
		{
           dup2(*input_fd, STDIN_FILENO);
            dup2(pip->tub[1], STDOUT_FILENO);
            close(*input_fd);
            close(pip->tub[0]);
            close(pip->tub[1]);
        }
		else if (pip->last == 1)
		{
  			dup2(*input_fd, STDIN_FILENO);
            close(*input_fd);
        }
		ft_excut_cmd_line(lst,args,pip);
		// ft_execute_command(env_path,cmd->cmd);
	}
	else
	{
		if (pip->first==1)
		{
			close(pip->tub[1]);
			*input_fd = pip->tub[0];
		}
		else if (pip->first==0 && pip->last==0)
		{
			close(*input_fd);
			close(pip->tub[1]);
			*input_fd = pip->tub[0];			
		}
		else if (pip->last == 1)
			close(*input_fd);
	}	
}
void	ft_lst_cmd(t_cmd	*command,t_lst_env *lst,t_data *pip)
{
	t_cmd	*cur;
	cur = command;
	int input_fd = -1;

	int	i = 0;
	while(cur->next)
	{
		if (i==0)
		{
			pip->first = 1;
			pip->last = 0;
		}
		else
		{
			pip->first = 0;
			pip->last = 0;
		}
		ft_excut_child(cur,pip,lst,&input_fd);
		cur = cur->next;
		i++;
	}
	pip->first = 0;
	pip->last = 1;
	ft_excut_child(cur,pip,lst,&input_fd); /*1 - 0*/
	while (wait(NULL) != -1)
		;
}
