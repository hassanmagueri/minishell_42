 
#include "minishell.h"

void	free_2d_arr(char **str)
{
	int i;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

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

void	process_child(t_redir	*red,t_data *pip, int is_last)
{
	char	*command;
	int tub[2];
	pid_t pid;
	command = NULL;
	if (!is_last)
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
		if (red->redirection_type == APPEND || red->redirection_type == OUTPUT)
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

// void	ft_here_doc(t_data *pip,t_redir *cur)
// {
// 	int		fds[2];
// 	char	*str;

// 	if (pipe(fds) == -1)
// 		printf("error in pipe");
// 	cur->str = ft_strjoin(cur->str, "\n");
// 	while (1)
// 	{
// 		ft_putstr_fd("> ", 1);
// 		str = get_next_line(0);
// 		if (str == NULL || (ft_strncmp(cur->str, str, ft_strlen(cur->str) != 1)))
// 		{
// 			free(str);
// 			break ;
// 		}
// 		ft_putstr_fd(str, fds[1]);
// 		free(str);
// 	}
// 	close (fds[1]);
// 	if (dup2(fds[0], STDIN_FILENO) == -1)
// 		printf("Error in dup2");
// 	close (fds[0]);
// }

void ft_excut_cmd(t_redir	*red,t_data *pip,int i)
{
	t_redir	*cur;
	cur = red;
	while(cur)
	{
		if (cur->redirection_type == INPUT)
		{
			cur->infile = open(cur->str, O_RDONLY);
			dup2(cur->infile,STDIN_FILENO);
			close(cur->infile);
		}
		else if (cur->redirection_type == OUTPUT)
		{
			cur->outfile = open(cur->str,O_CREAT | O_WRONLY | O_TRUNC, 0666);
		}
		else if (cur->redirection_type == HEARDOC)
		{
			// ft_here_doc(cur,pip);
		}
		else if (cur->redirection_type == APPEND)
		{
			cur->outfile = open(cur->str, O_CREAT | O_WRONLY | O_APPEND, 0666);
			
		}
		cur = cur->next;
	}
	if (red->cmd != NULL)
		process_child(cur,pip,i);
}

void	ft_lst_cmd(t_cmd	*command, t_data *pip)
{
	t_cmd	*cur;
	cur = command;
	while(cur->next)
	{
		ft_excut_cmd(cur->redir,pip,0);
		cur = cur->next;
	}
	ft_excut_cmd(cur->redir,pip,1);//if last command excut with not pipein
}
void	inist_pipe(t_data *pip,char *evm[])
{
	while (evm && *evm && ft_strncmp(*evm, "PATH=", 5) != 0)
		evm++;
	if (*evm == NULL)
		printf("Path not found");
	*evm += 5;
	pip->env_path = ft_split (*evm, ':');
	if (!pip->env_path)
		printf("Invalid argument");
}
#include "minishell.h"
#include <stdio.h>

int main(int arc ,char **arv,char **env) {
    t_data pip;
    inist_pipe(&pip,env);
    t_redir red1, red2; // Example redirections
    red1.redirection_type = INPUT;
    red1.str = "input.txt";
    red1.next = &red2;
    red2.redirection_type = OUTPUT;
    red2.str = "output.txt";
    red2.next = NULL;

    t_cmd cmd1, cmd2; // Example commands
    cmd1.redir = &red1;
    cmd1.next = &cmd2;
    cmd2.redir = &red2;
    cmd2.next = NULL;

    ft_lst_cmd(&cmd1, &pip); // Execute the commands

    return 0;
}