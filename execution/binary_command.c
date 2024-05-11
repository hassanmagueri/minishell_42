/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/11 04:04:04 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	init_path_env(t_data *pip,t_lst_env *lst,char **env)
{
	char *str;
	pip->env = env;
	str = ft_get_env_val(&lst, "PATH");
	// printf("str   ->   %s\n",str);
	pip->env_path = ft_split(str, ':');
	if (!pip->env_path)
		printf("Invalid argument\n");
	pip->infile = -1;
	pip->outfile = -1;
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

int	ft_execute_command(t_data *pip,t_lst_env *lst,char **cmd)
{
	char *command;
	// init_path_env(pip,lst);
	command = find_path_executable(pip->env_path, cmd[0]);
	// int i = 0;
	// while(pip->env_path[i])
	//  	printf("%s\n",pip->env_path[i++]);
	if (command == NULL)
	{
		printf("%s :command not found\n",cmd[0]);
		return(127);
	}
	execve(command, cmd, pip->env);
	return (0);
	// free_2d_arr(cmd);
	// free(command);
}