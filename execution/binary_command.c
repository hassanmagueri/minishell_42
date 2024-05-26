/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/26 17:22:16 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
char *ft_str_env(char *s1,char *s2)
{
	char *str;
	str = ft_strjoin(s1,"=",ALLOC);
	str = ft_strjoin(str,s2,ALLOC);
	return (str);
}
//is_dir

int is_directory(char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)//
        return 0;
    return S_ISDIR(statbuf.st_mode);
}
//
char **ft_lst_to_tab(t_lst_env **lst)
{
	t_lst_env *cur;
	char **res;
	int cont ;
	int i = 0;
	cont = 0;
	cur = *lst;
	if (*lst == NULL)
		return (NULL);
	while(cur)
	{
		cont++;
		cur = cur->next;
	}
	res = gc_alloc((cont + 1) * sizeof(char *), ALLOC_ENV);
	cur = *lst;
	while (cur)
	{
		if (cur->value != NULL)
		{
			res[i] = ft_str_env(cur->key,cur->value);
			i++;
		}
		cur = cur->next;
	}
	res[i] = NULL;
	return (res);
}

void	init_path_env(t_data *pip,t_lst_env **lst)
{
	char *str;
	pip->env = ft_lst_to_tab(lst);
	str = ft_get_env_val(lst, "PATH");
	pip->env_path = ft_split(str, ':', ALLOC_ENV);
	if (!pip->env_path)
		return ;
		// printf("%s\n",)
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
	if(cmd[0]=='\0')
		return NULL;
	if (parsing_cmd(cmd) != 0)
	{
		if (access(cmd, X_OK) == 0 && access(cmd, F_OK) == 0)
		{
			if (is_directory(cmd))
			{
				ft_putstr_fd(cmd,2);
				ft_putendl_fd(": is a directory",2);
				exit(126);	
			}
			return (cmd);
		}
		if (parsing_cmd(cmd) == -1)
		{
			// printf("%s: Permission denied\n",cmd);
			ft_putstr_fd(cmd,2);
			ft_putendl_fd(": Permission denied",2);
			// perror(cmd);
			exit(126);
		}
		else
		{
			perror(cmd);
			exit(127);
		}
	}
	if (!env_path)
	{
		// printf("%s: No such file or directory\n",cmd);
		ft_putstr_fd(cmd,2);
		ft_putendl_fd(": No such file or directory",2);
		exit(127);
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

int	ft_execute_command(t_data *pip,t_lst_env **lst,char **cmd)
{
	char *command;
	init_path_env(pip,lst);
	if (cmd[0] == NULL || (cmd[0][0]==':' && cmd[0][1]== '\0' ))
		exit (0);
	command = find_path_executable(pip->env_path, cmd[0]);
	if (command == NULL)
	{
		ft_putstr_fd(cmd[0],2);
		ft_putendl_fd(" :command not found",2);
		exit(127);
	}
	execve(command, cmd, pip->env);
	return (0);
}
