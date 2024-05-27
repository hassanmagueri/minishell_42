/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:18:53 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 17:36:36 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_change_value_dir(t_lst_env **lst, char *pwd, char *oldpwd, char *str)
{
	pwd = ft_get_pwd(lst, pwd, oldpwd, str);
	if (pwd == NULL)
		return (1);
	if (ft_change_directory(*lst, pwd, str) == 1)
		return (1);
	if (ft_check_value_node(lst, "OLDPWD") == 0)
		ft_change_value_lst(lst, "OLDPWD", oldpwd);
	else
		ft_lst_add_back_env(lst, ft_new_env("OLDPWD", oldpwd));
	return (0);
}

char	*ft_get_pwd(t_lst_env **lst, char *pwd, char *oldpwd, char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL)
	{
		pwd = ft_get_env_val(lst, "HOME");
		if (pwd == NULL)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
		return (pwd);
	}
	if (ft_strncmp(cmd, "..", 3) == 0)
	{
		pwd = ft_get_newpwd_path(pwd);
		return (pwd);
	}
	if (ft_strncmp(cmd, ".", 2) == 0)
		return (pwd);
	cmd = ft_strjoin(oldpwd, cmd, ALLOC);
	return (cmd);
}

int	ft_chdir_oldpwd(t_lst_env **lst)
{
	char	*pwd;
	char	*oldpwd;
	char	cmd[1024];

	pwd = getcwd(cmd, sizeof(cmd));
	if (ft_check_value_node(lst, "OLDPWD") == 0)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		return (1);
	}
	else
	{
		oldpwd = ft_get_env_val(lst, "OLDPWD");
		ft_change_value_lst(lst, "PWD", oldpwd);
		if (chdir(oldpwd) != 0)
		{
			ft_putendl_fd("cd: OLDPWD not set", 2);
			return (1);
		}
		ft_change_value_lst(lst, "OLDPWD", pwd);
		printf("%s\n", oldpwd);
	}
	return (0);
}

int	ft_not_access_parent(t_lst_env **lst, char *str, char *pwd)
{
	char	*oldpwd;
	char	cmd[1024];

	if (access(str, F_OK) == 0)
	{
		if (chdir(str) != 0)
			perror("cd");
		if (getcwd(cmd, sizeof(cmd)) == NULL)
			error_msg();
	}
	else
	{
		perror("cd");
		return (1);
	}
	ft_change_value_lst(lst, "PWD", cmd);
	ft_change_value_lst(lst, "OLDPWD", pwd);
	return (0);
}

int	ft_cd(t_lst_env **lst, t_cmd *args)
{
	char	*pwd;
	char	*oldpwd;
	char	cmd[1024];
	int		status;

	status = 0;
	pwd = getcwd(cmd, sizeof(cmd));
	if (pwd == NULL)
		status = ft_not_access_parent(lst, args->cmd[1], cmd);
	else
	{
		oldpwd = pwd;
		if (args->cmd[1] != NULL
			&& args->cmd[1][0] == '-' && args->cmd[1][1] == '\0')
		{
			if (ft_chdir_oldpwd(lst) == 1)
				return (1);
		}
		else
			status = ft_change_value_dir(lst, pwd, oldpwd, args->cmd[1]);
	}
	return (status);
}
