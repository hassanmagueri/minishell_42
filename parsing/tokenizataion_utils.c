/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizataion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:18:32 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_with_spaces(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	is_sep(int c)
{
	return (ft_is_with_spaces(c) || c == '|' || c == '\"'
		|| c == '\'' || c == '<' || c == '>' || c == '|' || c == '$');
}

int	find_sec(char *s, char c)
{
	int	i;

	if (!s[0])
		return (-1);
	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_token_redir(t__lst_token **token, char *input)
{
	int	i;

	i = 0;
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			ft_lst_token_add_back(token,
				ft_new_token(ft_substr(input, i++, 2, ALLOC), HEARDOC));
		else
			ft_lst_token_add_back(token,
				ft_new_token(ft_substr(input, i, 1, ALLOC), INPUT));
		i++;
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			ft_lst_token_add_back(token,
				ft_new_token(ft_substr(input, i++, 2, ALLOC), APPEND));
		else
			ft_lst_token_add_back(token,
				ft_new_token(ft_substr(input, i, 1, ALLOC), OUTPUT));
		i++;
	}
	return (i);
}
