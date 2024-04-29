/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:18:53 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/29 10:41:47 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_change_value_lst(t_lst_env	**lst_env,char *key,char *value)
{
	t_lst_env	*cur;
	cur = *lst_env;

	while(cur)
	{
		if (ft_strncmp(cur->key,key,ft_strlen(cur->key)) == 0)
		{
			cur->value = ft_strdup(value);
			return(0);
		}
		cur = cur->next;
	}
	return(1);
}

int	ft_find_node(t_lst_env **lst_env, char *key)
{
	t_lst_env *cur;
	cur = *lst_env;
	while (cur)
	{
		if (ft_strncmp(cur->key,key,ft_strlen(cur->key))== 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}
char *ft_get_newpwd_path(char *pwd)
{
	int len;
	char *str;
	len = ft_strlen(pwd);
	len--;
	while(pwd[len])
	{
		if (pwd[len] != '/')
			len--;
		else
			break;
	}
	if (len == 0)
		str = ft_strdup("/");
	else
		str = ft_substr(pwd, 0, len);
	return (str);
}

int    ft_cd(t_lst_env *lst,t_cmd  *args)
{
	char	*pwd;
	char	*oldpwd;
	char cmd[1024];
	char **str;
	int i = 0;
	pwd =getcwd(cmd, sizeof(cmd));
	oldpwd = pwd;
	if (args->cmd[1][0]=='\0')
		return (0);
	str = ft_split(args->cmd[1], '/');
	if (str[i]== NULL)
	{
		pwd = ft_strdup("/");
		if (chdir(pwd)!= 0)
			perror("Failed to change directory");
		return (0);
	}
	while(str[i])
	{
		if(ft_strncmp(str[i],"..",2) == 0)
		{
			pwd = ft_get_newpwd_path(pwd);
			i++;
		}
		else if(ft_strncmp(str[i],".",1) == 0)
			i++;
		else
		{
			str[i] = ft_strjoin(str[i], "/");
			pwd = ft_strjoin(pwd,str[i]);
			i++;
		}
	}
	if(access(pwd,F_OK) == 0)
	{
		if (chdir(pwd)!= 0)
				perror("Failed to change directory");
		ft_change_value_lst(&lst, "PWD", pwd);
	}
	else if(access(args->cmd[1],F_OK) == 0)
	{
		if (chdir(args->cmd[1])!=0)
			perror("Failed to change directory");
		ft_change_value_lst(&lst, "PWD", args->cmd[1]);
	}
	else
		perror("cd");
	if (ft_find_node(&lst,"OLDPWD")== 0)
		ft_change_value_lst(&lst, "OLDPWD", oldpwd);
	else
		ft_lst_add_back_env(&lst, ft_new_env("OLDPWD", oldpwd));
	return (0);
}
// case cd -
