/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:34:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/30 00:00:11 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_expand_var(char *input, t_lst_env **lst_env, int *index)
{
	int		start;
	int		i;
	char	*var;
	char	*new_input;

	new_input = "";
	if (input[0] == '$')
	{
		*index += 1;
		var = ft_handle_var(lst_env, input + 1, index);
		if (var == NULL)
			var = "";
		new_input = ft_strjoin(new_input, var, ALLOC);
	}
	else
	{
		i = *index;
		start = i;
		while (input[i] && input[i] != '$')
			i++;
		new_input = ft_strjoin(new_input,
				ft_substr(input, start, i - start, ALLOC), ALLOC);
		*index = i;
	}
	return (new_input);
}

char	*ft_expend_input(char *input, t_lst_env **lst_env)
{
	int		i;
	int		start;
	char	*new_input;

	i = 0;
	new_input = "";
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] == '$')
		{
			start = i;
			i += 2;
			new_input = ft_substr(input, start, i, ALLOC);
		}
		else
			new_input = ft_expand_var(input + i, lst_env, &i);
	}
	return (new_input);
}

int	ft_buffering_fake_heredoc(t__lst_token *token)
{
	char	*delimiter;
	char	*input;

	delimiter = ft_get_delimiter(token);
	if (delimiter == NULL)
		return (0);
	while (1)
	{
		if (isatty(0) == 0)
			return (1);
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(input);
			break ;
		}
		if (input)
			free(input);
	}
	return (0);
}

int	ft_fake_heredoc(t__lst_token **lst_token)
{
	t__lst_token	*token;
	int				sec_fd_in;

	(1) && (token = *lst_token, sec_fd_in = dup(0));
	signal(SIGINT, handle_heredoc);
	token = ft_get_token_by_type(&token, HEARDOC);
	while (token)
	{
		if (ft_buffering_fake_heredoc(token))
			break ;
		token = ft_next_token(&token);
		token = ft_get_token_by_type(&token, HEARDOC);
	}
	dup2(sec_fd_in, 0);
	close(sec_fd_in);
	return (1);
}
