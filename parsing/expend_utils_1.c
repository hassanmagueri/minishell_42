/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/29 23:52:38 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_handle_simple_string(char *old_output, char *new_output, int *index)
{
	int	len;
	int	i;

	i = *index + 1;
	len = 1;
	while (old_output[len] && old_output[len] != '$')
		len++;
	new_output = ft_strnjoin(new_output, old_output, len, ALLOC);
	(*index) += len;
	return (new_output);
}

char	*ft_handle_var(t_lst_env **lst_env, char *key, int *index)
{
	int		len;
	char	*s;

	len = 0;
	if (ft_isdigit(key[len]))
		len++;
	else
		while (key[len] && (ft_isalnum(key[len]) || key[len] == '_'))
			len++;
	s = ft_get_env_val(lst_env, ft_strnjoin("", key, len, ALLOC));
	if (!s)
		s = "";
	if (index != NULL)
		(*index) += len;
	return (s);
}
