/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:18:53 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/18 17:17:51 by ataoufik         ###   ########.fr       */
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
	if(access(pwd,F_OK) == 0)
	{
		if (chdir(pwd)!= 0)
				perror("cd");
		ft_change_value_lst(&lst, "PWD", pwd);
	}
	else if(access(args,F_OK) == 0)
	{
		if (chdir(args)!= 0)
			perror("Failed");
		ft_change_value_lst(&lst, "PWD", args);
	}
	else
		perror("cd");
	return(0);
}
char *ft_get_pwd(t_lst_env **lst, char *pwd,char *cmd)
{
	int i;
	i = 0;

	if (cmd == NULL)
	{
		pwd = ft_get_env_val(lst, "HOME");
		return (pwd);
	}
	if(ft_strncmp(cmd,"..",3) == 0)	
	{
		pwd = ft_get_newpwd_path(pwd);
		return (pwd);
	}
	if(ft_strncmp(cmd,".",2) == 0)	
	{
		return (pwd);
	}
	// while(cmd[i])
	// {
	// 	if (cmd[i]=='/' || cmd[i]=='.')
	// 	{
	// 		if (cmd[i + 1]=='.' &&  cmd[i + 2]=='.')
	// 			return (cmd);
	// 		i++;
	// 	}
	// 	else
	// 		return (cmd);
	// }
	// pwd = cmd;
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
			perror("cd ");
		ft_change_value_lst(lst, "OLDPWD", pwd);
		printf("%s\n",oldpwd);
	}
	return (0);
}

int    ft_cd(t_lst_env **lst,t_cmd  *args)
{
	char	*pwd;
	char	*oldpwd;
	char cmd[1024];
	int	status = 0;
	char **str;
	status = 0;
	pwd = getcwd(cmd, sizeof(cmd));
	oldpwd = pwd;
	if (args->cmd[1] != NULL && args->cmd[1][0] == '-' && args->cmd[1][1] == '\0')
		ft_chdir_oldpwd(lst);
	else if(args->cmd[1] != NULL && args->cmd[1][0] == '-' && args->cmd[1][1] != '\0')
	{
		printf("cd: -%c: invalid option\n",args->cmd[1][1]);
		status = 1;
	}
	else
	{
		pwd = ft_get_pwd(lst,pwd,args->cmd[1]);
		ft_change_directory(*lst, pwd, args->cmd[1]);
		if (ft_check_value_node(lst,"OLDPWD") == 0)
			ft_change_value_lst(lst, "OLDPWD", oldpwd);
		else
			ft_lst_add_back_env(lst, ft_new_env("OLDPWD", oldpwd));
	}
	return (status);
}

