/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/14 14:49:15 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	init_path_env(t_data *pip,t_lst_env *lst,char **env)
{
	char *str;
	pip->env = env;
	str = ft_get_env_val(&lst, "PATH");
	// printf("str   ->   %s\n",str);
	pip->env_path = ft_split(str, ':', ALLOC_ENV);
	if (!pip->env_path)
		return ;
	pip->infile = -1;
	pip->outfile = -1;
}
int	parsing_cmd(char *str)
{
	int i;
	i = 0;
	if (str[0]=='.' && str[1]== '/')
		return (-1);
	while(str[i])
	{
		if (str[i]=='/')
			return (1);
		i++;
	}
	return 0;
}
char	*find_path_executable(char **env_path, char *cmd)
{
	char	*str;
	char	*path;
	int		i;

	i = 0;
	str = NULL;
	path = NULL;
	if (!env_path)
		return NULL;
	if (parsing_cmd(cmd) != 0)
	{
		if (access(cmd, X_OK) == 0 && access(cmd, F_OK) == 0)
			return (cmd);
		else if (parsing_cmd(cmd) == -1)
		{
			printf("%s: Permission denied\n",cmd);
			exit(126);
		}
		else
		{
			printf("%s: No such file or directory\n",cmd);
			exit(127);
		}
	}
	while (env_path[i])
	{
		str = ft_strjoin(env_path[i], "/", ALLOC);
		path = ft_strjoin(str, cmd, ALLOC);
		free(str);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	return (NULL);
}

int	ft_execute_command(t_data *pip,t_lst_env *lst,char **cmd)
{
	char *command;
	command = find_path_executable(pip->env_path, cmd[0]);
	if (command == NULL)
	{
		printf("%s :command not found\n",cmd[0]);
		exit(127);
	}
	execve(command, cmd, pip->env);
	return (0);
}