/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 10:38:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/30 11:49:57 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_arg(char *str)
{
	int i = 1;

	if (str == NULL || str[0] != '-')
		return 0;
	while (str[i])
		if (str[i++] != 'n')
			return (0);
	return (1);
}

void print_echo(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	
}

int ft_echo(t_cmd *cmd)
{
	char **cmd_str;
	int	i;

	cmd_str = cmd->cmd + 1;
	i = 0;
	while (ft_is_arg(cmd_str[i]))
		i++;
	print_echo(cmd_str + i);
	if (i == 0)
		printf("\n");
	return 1;
}
