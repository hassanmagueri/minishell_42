/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:32:53 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/23 00:05:42 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_envlen(char **str)
{
	int n;
	while(*str)
	{
		str++;
		n++;
	}
	return (n);
}

char	**ft_dup_env(char **env)
{
	int		i;
	int		len_env;
	char	**new_env;

	i = 0;
	len_env = ft_envlen(env);
	new_env = (char **)malloc(sizeof(char *) * (len_env + 1));
	if (!new_env)
		return (NULL);
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
void	ft_env(char **new_env)
{
	int	i;

	i = 0;
	while(new_env[i])
	{
		ft_putendl_fd(new_env[i], 1);
		i++;
	}
}


int main(int ac,char *av[],char *env[])
{
	int n;
	int	i;
	char **str;
	i = 0;

	n = ft_envlen(env);
	str = ft_dup_env(env);
	printf("envlen = %d\n",n);
	while(str[i])
		printf("%s\n",str[i++]);
}