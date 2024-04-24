#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

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
void process_child(char **cmd, t_redir *red, char **env_path, int is_last)
{
    int tub[2];
    pid_t pid; 
    if (is_last == 0)
	{
        if (pipe(tub) == -1)
		{
            perror("pipe");
            exit(1);
        }
    }
    pid = fork();
    if (pid == 0)
	{
        if (is_last == 0)
		{
            close(tub[0]);
            dup2(tub[1], STDOUT_FILENO);
            close(tub[1]);
        }
        ft_execute_command(env_path, cmd);
		// ft_execute_command(env_path,cmd,command);
    } 
	else if (pid > 0)
	{
        if (is_last == 0){
            close(tub[1]); 
    	        dup2(tub[0], STDIN_FILENO);
            close(tub[0]);
        }
	}
}

void ft_excut_cmd(char **cmd,t_redir *redir ,char **env_path,int i)
{
	t_redir	*cur;
	cur = redir;
	while(cur)
	{
		if (cur->redirection_type == INPUT)
		{
			cur->infile = open(cur->file_name, O_RDONLY);
			dup2(cur->infile,STDIN_FILENO);
			close(cur->infile);
		}
		else if (cur->redirection_type == OUTPUT)
		{
			cur->outfile = open(cur->file_name,O_CREAT | O_WRONLY | O_TRUNC, 0666);
		}
		else if (cur->redirection_type == HEARDOC)
		{
			// ft_here_doc(cur,pip);
		}
		else if (cur->redirection_type == APPEND)
		{
			cur->outfile = open(cur->file_name, O_CREAT | O_WRONLY | O_APPEND, 0666);
			
		}
		cur = cur->next;
	}
	if (cmd != NULL)
		process_child(cmd,redir,env_path,i);
}

void	ft_lst_cmd(t_cmd	*command, char **env_path)
{
	t_cmd	*cur;
	cur = command;
	if (!cur)
		return ;
	// int i =1;
	// int j;
	while(cur->next)
	{
		// process_child(cur->cmd, cur->redir, env_path, 0);
		ft_excut_cmd(cur->cmd,cur->redir ,env_path,0);
		// j = 0;
		// while(cur->cmd[j])
		// 	printf("%s-->",cur->cmd[j++]);
		// printf("%s-->",cur->cmd[j++]);
		// printf("\n-----------------\n");
		// printf("%d\n",i++);
		cur = cur->next;
	}
	ft_excut_cmd(cur->cmd,cur->redir ,env_path,1);//if last command excut with not pipein
	while (wait(NULL) != -1)
		;
		return;
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> // For open() flags
#include <readline/readline.h>
#include <readline/history.h>


// (Your code for 'free_2d_arr', 'find_path_executable', 'ft_execute_command', 'process_child', 'ft_excut_cmd', 'ft_lst_cmd' goes here)

int main(int argc, char **argv)
{
    char **env_path = (char*[]){"/bin", "/usr/bin", NULL};

    while (1)
    {
        char *input = readline("minishell> ");
        
        if (input == NULL) // Handle Ctrl+D or empty input
        {
            printf("Exiting shell.\n");
            free(input);
            break;
        }

        add_history(input); // Add to command history
        
        // Example: Parsing input and constructing pipeline
        char *cmd1[] = {"/bin/ls", "-l", NULL};
        char *cmd2[] = {"/usr/bin/grep", input, NULL};
        char *cmd3[] = {"/usr/bin/sort", "-r", NULL};
        char *cmd4[] = {"/usr/bin/head", "-n", "5", NULL};

        t_redir no_redir = {0, -1};
        
        t_cmd command1 = {cmd1, &no_redir, NULL};
        t_cmd command2 = {cmd2, &no_redir, NULL};
        t_cmd command3 = {cmd3, &no_redir, NULL};
        t_cmd command4 = {cmd4, &no_redir, NULL};

        command1.next = &command2;
        command2.next = &command3;
        command3.next = &command4;

        ft_lst_cmd(&command1, env_path); // Execute pipeline
        
        free(input); // Clean up allocated memory
    }

    return 0; // Successful execution
}