/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:38:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/18 15:47:55 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"
char *ft_str_env(char *s1,char *s2)
{
	char *str;
	// if (!s2)
	str = ft_strjoin(s1,"=",ALLOC);
	str = ft_strjoin(str,s2,ALLOC);
	return (str);
}
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
	pip->infile = 0;
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
	// if 
	if (!env_path)
	{
		printf("%s: No such file or directory\n",cmd);
		exit(127);
	}
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

int	ft_execute_command(t_data *pip,t_lst_env **lst,char **cmd)
{
	// signal(SIGINT, SIG_DFL);
	// signal(SIGQUIT, SIG_DFL);
	char *command;
	if (cmd[0] == NULL || (cmd[0][0]==':'&&cmd[0][1]=='\0' ))
		exit (0);
	command = find_path_executable(pip->env_path, cmd[0]);
	// printf("%s\n",command);
	if (command == NULL)
	{
		printf("%s :command not found\n",cmd[0]);
		exit(127);
	}
	// int i = 0;
	// t_lst_env *cur;
	// cur = *lst;
	// while (cur)
	// {
	// 	i++;
	// 	// printf("%s\n",cur->key);
	// 	cur = cur->next;
	// }
	// printf("env count before %d \n", i);
	execve(command, cmd, pip->env);
	return (0);
}
