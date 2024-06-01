/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/06/01 09:56:22 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_path_env(t_data *pip, t_lst_env **lst)
{
	char	*str;

	pip->env = ft_lst_to_tab(lst);
	str = ft_get_env_val(lst, "PATH");
	pip->env_path = ft_split(str, ':', ALLOC_ENV);
	if (!pip->env_path)
		return ;
}

int	parsing_cmd(char *str)
{
	int	i;

	i = 0;
	if ((str[0] == '.' && str[1] == '\0')
		|| (str[0] == '.' && str[1] == '.' && str[2] == '\0'))
		return (2);
	if (str[0] == '.' && str[1] == '/')
		return (-1);
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_command(char *cmd)
{
	if (parsing_cmd(cmd) != 0)
	{
		if (access(cmd, X_OK) == 0 && access(cmd, F_OK) == 0)
		{
			if (is_directory(cmd))
				exit(error_msg_cmd(cmd, 0));
			return (0);
		}
		if (parsing_cmd(cmd) == -1)
			exit(error_msg_cmd(cmd, 2));
		else
		{
			perror(cmd);
			exit(127);
		}
	}
	return (1);
}

char	*find_path_executable(char **env_path, char *cmd)
{
	char	*str;
	char	*path;
	int		i;

	i = 0;
	str = NULL;
	path = NULL;
	if (cmd[0] == '\0' || parsing_cmd(cmd) == 2)
		return (NULL);
	if (ft_check_command(cmd) == 0)
		return (cmd);
	if (!env_path)
		exit(error_msg_cmd(cmd, 1));
	while (env_path[i])
	{
		str = ft_strjoin(env_path[i], "/", ALLOC);
		path = ft_strjoin(str, cmd, ALLOC);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

int	ft_execute_command(t_data *pip, t_lst_env **lst, char **cmd)
{
	char	*command;

	init_path_env(pip, lst);
	if (cmd[0] == NULL || (cmd[0][0] == ':' && cmd[0][1] == '\0' ))
		exit (0);
	command = find_path_executable(pip->env_path, cmd[0]);
	if (command == NULL)
		exit(error_msg_cmd(cmd[0], 3));
	execve(command, cmd, pip->env);
	return (0);
}
