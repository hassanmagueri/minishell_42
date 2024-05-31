/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:07:15 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/31 12:09:58 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_msg_exit(char *str, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("exit: ", 2);
		if (str != NULL)
			ft_putstr_fd(str, 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (255);
	}
	else
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
}

int	ft_parsing_exit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_skip_zero(char *str)
{
	char	*res;
	int		len;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (str[0] == '-' || str[0] == '+')
		len++;
	res = gc_alloc((len + 1) * sizeof(char), ALLOC);
	if (!res)
		return (NULL);
	if (str[0] == '-' || str[0] == '+')
		res[j++] = str[0];
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	return (res);
}
