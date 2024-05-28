/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:18:39 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/28 15:43:53 by ataoufik         ###   ########.fr       */
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

long long int	ft_number_exit(char *str)
{
	long long			num;
	int					i;
	int					sig;

	sig = 1;
	i = 0;
	num = 0;
	if (str == NULL)
		return (error_msg_exit(NULL, 1));
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i])
	{
		num = num * 10 + str[i] - 48;
		if (num != 0 && ((num > LLONG_MAX && sig == 1)
				|| (num - 1 > LLONG_MAX && sig == -1)))
			return (error_msg_exit(str, 1));
		else
			i++;
	}
	return (num * sig);
}

int	ft_len_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_exit(t_cmd *args, int *ex_state)
{
	char	**str;
	int		i;

	i = 1;
	ft_putendl_fd("exit", 1);
	if (args->cmd[1] == NULL)
		exit(*ex_state);
	str = ft_split_space_tab(args->cmd[1], ALLOC);
	if (ft_len_tab(str) > 1)
		return (error_msg_exit(NULL, 0));
	else if (ft_parsing_exit(str[0]) == 0 && i == 1 && args->len == 1)
		exit(ft_number_exit(str[0]) % 256);
	while (args->cmd[i])
	{
		if (i >= 2 && ft_parsing_exit(args->cmd[1]) == 0)
			return (error_msg_exit(NULL, 0));
		if (ft_parsing_exit(args->cmd[i]) == 1)
			exit(error_msg_exit(args->cmd[i], 1));
		i++;
	}
	if (i == 2)
		exit (ft_number_exit(args->cmd[1]) % 256);
	return (0);
}
