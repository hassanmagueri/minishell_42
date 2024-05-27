/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:38:06 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 17:36:53 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(void)
{
	ft_putstr_fd("cd: error retrieving current directory", 2);
	ft_putstr_fd(": getcwd: cannot access parent directories", 2);
	ft_putendl_fd(": No such file or directory", 2);
}

int	ft_change_value_lst(t_lst_env	**lst_env, char *key, char *value)
{
	t_lst_env	*cur;

	cur = *lst_env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0)
		{
			cur->value = ft_strdup(value, ALLOC_ENV);
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	ft_check_value_node(t_lst_env **lst_env, char *key)
{
	t_lst_env	*cur;

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

char	*ft_get_newpwd_path(char *pwd)
{
	char	*str;
	int		len;

	len = ft_strlen(pwd);
	len--;
	if (len == -1)
	{
		pwd = ft_strjoin(pwd, "/", ALLOC);
		pwd = ft_strjoin(pwd, "..", ALLOC);
		return (pwd);
	}
	while (pwd[len])
	{
		if (pwd[len] != '/')
			len--;
		else
			break ;
	}
	if (len == 0)
		str = ft_strdup("/", ALLOC);
	else
		str = ft_substr(pwd, 0, len, ALLOC);
	return (str);
}

int	ft_change_directory(t_lst_env *lst, char *pwd, char *args)
{
	char	cmd[1024];

	if (access(args, F_OK) == 0)
	{
		if (chdir(args) != 0)
			perror("Failed");
		pwd = getcwd(cmd, sizeof(cmd));
		ft_change_value_lst(&lst, "PWD", pwd);
	}
	else if (args == NULL)
	{
		if (chdir(pwd) != 0)
			perror("Failed");
		ft_change_value_lst(&lst, "PWD", pwd);
	}
	else
	{
		perror("cd");
		return (1);
	}
	return (0);
}
