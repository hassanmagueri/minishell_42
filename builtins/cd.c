/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:18:53 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/24 21:58:22 by ataoufik         ###   ########.fr       */
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
			cur->value = ft_strdup(value, ALLOC);
			return(0);
		}
		cur = cur->next;
	}
	return(1);
}

int	ft_check_value_node(t_lst_env **lst_env, char *key)
{
	t_lst_env *cur;
	cur = *lst_env;
	while (cur)
	{
		
		if (ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
		{
			if (cur->value == NULL)
				return (0);
		}
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
	printf("%s\n",pwd);
	if (len == -1)
	{
		pwd = ft_strjoin(pwd ,"/",ALLOC);
		pwd = ft_strjoin(pwd,"..",ALLOC);
		return pwd;
	}
	while(pwd[len])
	{
		if (pwd[len] != '/')
			len--;
		else
			break;
	}
	if (len == 0) 
		str = ft_strdup("/", ALLOC);
	else
		str = ft_substr(pwd, 0, len, ALLOC);
	return (str);
}
int ft_change_directory(t_lst_env *lst,char *pwd,char *args)
{
	char cmd[1024];
	if(access(args,F_OK) == 0)
	{
		if (chdir(args)!= 0)
			perror("Failed");
		pwd = getcwd(cmd, sizeof(cmd));
		ft_change_value_lst(&lst, "PWD", pwd);
	}
	else if (args == NULL)
	{
		if (chdir(pwd)!= 0)
			perror("Failed");
		ft_change_value_lst(&lst, "PWD", pwd);
	}
	else
		perror("cd");
	return(0);
}
char *ft_get_pwd(t_lst_env **lst, char *pwd,char *oldpwd,char *cmd)
{
	int i;
	i = 0;

	if (cmd == NULL)
	{
		pwd = ft_get_env_val(lst, "HOME");
		if (pwd == NULL)
		{
			ft_putendl_fd("cd: HOME not set",2);
			return NULL;
		}
		return (pwd);
	}
	if(ft_strncmp(cmd,"..",3) == 0)	
	{
		pwd = ft_get_newpwd_path(pwd);
		return (pwd);
	}
	if(ft_strncmp(cmd,".",2) == 0)	
		return (pwd);
	cmd = ft_strjoin(oldpwd, cmd,ALLOC);
	return (cmd);
}

int	ft_chdir_oldpwd(t_lst_env **lst)
{
	char *pwd;
	char *oldpwd;
	char cmd[1024];
	pwd = getcwd(cmd, sizeof(cmd));
	if (ft_check_value_node(lst,"OLDPWD") == 0)
	{
		printf("cd: OLDPWD not set\n");
		return (1);
	}
	else
	{
		oldpwd = ft_get_env_val(lst, "OLDPWD");
		ft_change_value_lst(lst, "PWD",oldpwd);
		if (chdir(oldpwd) != 0)
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		ft_change_value_lst(lst, "OLDPWD", pwd);
		printf("%s\n",oldpwd);
	}
	return (0);
}
int ft_not_access_parent(t_lst_env **lst ,char *str)
{
	char *pwd;
	char *oldpwd;
	char cmd[1024];
	pwd = ft_get_env_val(lst, "PWD");
	oldpwd = pwd;
	if(access(str,F_OK) == 0)
	{
		if (chdir(str) != 0)
			perror("cd");
		if (getcwd(cmd, sizeof(cmd))== NULL)	
			printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	}
	else
	{
		perror("cd");
		return (1);
	}
	pwd = ft_strjoin(pwd,"/",ALLOC);
	pwd = ft_strjoin(pwd,str,ALLOC);
	ft_change_value_lst(lst, "PWD", pwd);
	ft_change_value_lst(lst, "OLDPWD", oldpwd);
	return (1);
}

int    ft_cd(t_lst_env **lst,t_cmd  *args)
{
	char	*pwd;
	char	*oldpwd;
	char cmd[1024];
	int	status ;
	char **str;
	status = 0;
	pwd = getcwd(cmd, sizeof(cmd));
	if (pwd == NULL)
		status = ft_not_access_parent(lst,args->cmd[1]);
	else
	{
		oldpwd = pwd;
		if (args->cmd[1] != NULL && args->cmd[1][0] == '-' && args->cmd[1][1] == '\0')
		{
			if (ft_chdir_oldpwd(lst)==1)
				return (1);
		}
		else
		{
			pwd = ft_get_pwd(lst,pwd,oldpwd,args->cmd[1]);
			printf("%s\n",pwd);
			if (pwd == NULL)
				return (1);
			ft_change_directory(*lst, pwd, args->cmd[1]);
			if (ft_check_value_node(lst,"OLDPWD") == 0)
				ft_change_value_lst(lst, "OLDPWD", oldpwd);
			else
				ft_lst_add_back_env(lst, ft_new_env("OLDPWD", oldpwd));
		}
	}
	return (status);
}

