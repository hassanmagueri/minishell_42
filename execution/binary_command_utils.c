/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:10:30 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 19:28:02 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_str_env(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, "=", ALLOC_ENV);
	str = ft_strjoin(str, s2, ALLOC_ENV);
	return (str);
}

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	len_lst(t_lst_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_lst_to_tab(t_lst_env **lst)
{
	t_lst_env	*cur;
	char		**res;
	int			cont;
	int			i;

	i = 0;
	cont = 0;
	cur = *lst;
	if (*lst == NULL)
		return (NULL);
	cont = len_lst(cur);
	res = gc_alloc((cont + 1) * sizeof(char *), ALLOC_ENV);
	while (cur)
	{
		if (cur->value != NULL)
		{
			res[i] = ft_str_env(cur->key, cur->value);
			i++;
		}
		cur = cur->next;
	}
	res[i] = NULL;
	return (res);
}

int	error_msg_cmd(char *str, int i)
{
	if (i == 0 || i == 2)
	{
		ft_putstr_fd(str, 2);
		if (i == 0)
			ft_putendl_fd(": is a directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
		return (126);
	}
	else if (i == 1 || i == 3)
	{
		ft_putstr_fd(str, 2);
		if (i == 1)
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(" :command not found", 2);
		return (127);
	}
	return (0);
}
