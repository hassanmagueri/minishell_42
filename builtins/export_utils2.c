/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:06:16 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/27 18:24:10 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_msg_export(char *str)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

char	*ft_key(char *key, int len, char *str)
{
	if (len != -1)
		key = ft_substr(str, 0, len, ALLOC_ENV);
	else
		key = ft_strdup(str, ALLOC_ENV);
	return (key);
}

char	*ft_value(char *value, int len, char *str)
{
	if (len != -1)
		value = ft_strdup(ft_strchr(str, '=') + 1, ALLOC_ENV);
	else
		value = ft_strdup(NULL, ALLOC_ENV);
	return (value);
}
