/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/04 22:06:40 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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
	{
		printf("%s :command not found\n",cmd[0]);
		exit(0);
	}
	execve(command, cmd, NULL);
	// free_2d_arr(cmd);
	// free(command);
}