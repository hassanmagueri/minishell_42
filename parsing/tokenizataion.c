/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizataion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:18:30 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tokenize_quotes(t__lst_token **token, char *input)
{
	int				len;
	char			quote;
	char			*str;
	t__lst_token	*node;

	node = NULL;
	quote = '\"';
	if (*input == '\'')
		quote = '\'';
	len = find_sec(input, quote) + 1;
	if (len == 0)
		len++;
	str = ft_substr(input, 0, len, ALLOC);
	if (quote == '\"')
		node = ft_new_token(str, DOUB_Q);
	else if (quote == '\'')
		node = ft_new_token(str, SING_Q);
	ft_lst_token_add_back(token, node);
	return (len);
}

int	ft_token_var(t__lst_token **token, char *input)
{
	int	start;
	int	i;

	i = 0;
	start = 0;
	i++;
	if (ft_isdigit(input[i]))
		i++;
	else
		while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
			i++;
	ft_lst_token_add_back(token,
		ft_new_token(ft_substr(input, start, i - start, ALLOC), VAR));
	return (i);
}

int	ft_token_word(t__lst_token **token, char *input)
{
	int	i;
	int	start;

	start = 0;
	i = 0;
	if (input[i] == '$' && (input[i + 1] == '\"' || input[i + 1] == '\''))
	{
		i++;
		return (i);
	}
	if (input[start] == '$')
		i++;
	while (input[i] && !is_sep(input[i]))
		i++;
	ft_lst_token_add_back(token,
		ft_new_token(ft_substr(input, start, i - start, ALLOC), WORD));
	return (i);
}

int	ft_token_dollars_exit(t__lst_token **token, char *input, t_type type)
{
	int	i;

	i = 0;
	if (type == WSP)
	{
		while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
			i++;
		ft_lst_token_add_back(token, ft_new_token(" ", WSP));
	}
	else
	{
		ft_lst_token_add_back(token,
			ft_new_token(ft_substr(input, i, 2, ALLOC), type));
		i += 2;
	}
	return (i);
}

int	ft__lst_tokenize(t__lst_token **token, char *input)
{
	int	i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|')
			ft_lst_token_add_back(token,
				ft_new_token(ft_substr(input, i++, 1, ALLOC), PIPE));
		else if (input[i] == '<' || input[i] == '>')
			i += ft_token_redir(token, input + i);
		else if (input[i] == '\"' | input[i] == '\'')
			i += ft_tokenize_quotes(token, input + i);
		else if (ft_is_with_spaces(input[i]))
			i += ft_token_dollars_exit(token, input + i, WSP);
		else if (input[i] == '$' && input[i + 1] == '$')
			i += ft_token_dollars_exit(token, input + i, WORD);
		else if (input[i] == '$' && input[i + 1] == '?')
			i += ft_token_dollars_exit(token, input + i, EXIT_STATUS);
		else if (input[i] == '$'
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
			i += ft_token_var(token, input + i);
		else
			i += ft_token_word(token, input + i);
	}
	return (0);
}
