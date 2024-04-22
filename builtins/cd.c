/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:18:53 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/22 10:44:13 by ataoufik         ###   ########.fr       */
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

int    ft_cd(t_lst_env *lst,t_cmd  *args)
{
	char	*pwd;
	char	*oldpwd;
	char cmd[1024];
	char *str;
	str = args->cmd[1];
	oldpwd = getcwd(cmd, sizeof(cmd));
	if (ft_find_node(&lst,"OLDPWD")== 0)
		ft_change_value_lst(&lst, "OLDPWD", oldpwd);
	else
		ft_lst_add_back_env(&lst, ft_new_env("OLDPWD", oldpwd));
	if (ft_strncmp(args->cmd[1],"..",2) == 0)
	{
		int len = ft_strlen(oldpwd);
		len--;
		while(oldpwd[len])
		{
			if (oldpwd[len] != '/')
				len--;
			else
				break;
				args->cmd[1] = ft_substr(oldpwd, 0, len);
		}
		ft_change_value_lst(&lst, "PWD", args->cmd[1]);
		return (0);
	}
	else if (ft_strncmp(args->cmd[1],".",1) == 0)
	{
		ft_change_value_lst(&lst, "PWD", oldpwd);
		return (0);
	}
	else
	{
		oldpwd = ft_strjoin(oldpwd, "/");
		args->cmd[1] = ft_strjoin(oldpwd,args->cmd[1]);
		if (access(args->cmd[1], F_OK) == 0)
		{
			ft_change_value_lst(&lst, "PWD", args->cmd[1]);
			return (0);
		}
		if(access(str,F_OK) == 0)
		{
			ft_change_value_lst(&lst, "PWD", str);
			return (0);
		}
	}
	return (1);
}
// int main()
// {
//     t_lst_env *env_lst = ft_new_env("PWD", "/home/user");
//     env_lst->next = ft_new_env("LESS", "-R");
//     t_cmd cmd;
//     cmd.cmd = (char **)malloc(2 * sizeof(char *));
//     cmd.cmd[0] = "cd";
//     cmd.cmd[1] = ".";

//     int result = ft_cd(env_lst, &cmd);

//     if (result == 0)
//         printf("Changed directory successfully.\n");
//     else
//         printf("Failed to change directory.\n");

//     t_lst_env *current = env_lst;
//     while (current)
// 	{
//         printf("Key: %s, Value: %s\n", current->key, current->value);
//         current = current->next;
//     }

//     current = env_lst;
//     while (current)
// 	{
//         t_lst_env *temp = current;
//         current = current->next;
//         free(temp->key);
//         free(temp->value);
//         free(temp);
//     }

//     free(cmd.cmd);

//     return 0;
// }
