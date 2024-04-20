/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizataion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/20 11:00:40 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_sep(int c)
{
	return (c == ' ' || c == '|' || c == '\t' || c == '\"' || c == '\'' || c == '<' || c == '>' || c == '|' || c == '$');
}

int find_sec(char *s, char c)
{
	int i;

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
void ft_void(void)
{
	return ;
}

int ft__lst_tokenize(t__lst_token **token, char *input)
{
	int i;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i++, 1), PIPE));
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i++, 2), HEARDOC));
			else
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 1), INPUT));
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i++, 2), APPEND));
			else
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 1), OUTPUT));
			i++;
		}
		else if (input[i] == '\"')
		{
			int len = find_sec(input + i, '\"') + 1;
			if (len == 0)
				return (print_error(NULL));
			char *str = ft_substr(input, i, len);
			t__lst_token *t = ft_new_token(str, DOUB_Q);
			ft_lst_token_add_back(token, t);
			i += len;
		}
		else if (input[i] == '\'')
		{
			int len = find_sec(input + i, '\'') + 1;
			if (len == 0)
				return (print_error(NULL));
			char *str = ft_substr(input, i, len);
			t__lst_token *t = ft_new_token(str, SING_Q);
			ft_lst_token_add_back(token, t);
			i += len;
		}
		else if (input[i] == ' ')
		{
			while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
				i++;
			ft_lst_token_add_back(token, ft_new_token(" ", SPACE));
		}
		else if (input[i] == '$' && input[i + 1] == '$')
		{
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 2), WORD));
			i += 2;
		}
		else if (input[i] == '$' && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
		{
			int start = i;

			i++;
			if (ft_isdigit(input[i]))
				i++;
			else
				while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
					i++;
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, start, i - start), VAR));
		}
		else
		{
			int start = i;

			if (input[i] == '$' && (input[i + 1] == '\"' || input[i + 1] == '\''))
			{
				i++;
				continue;
			}
			if (input[start] == '$')
				i++;
			while (input[i] && !is_sep(input[i]))
				i++;
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, start, i - start), WORD));
		}
	}
	return (0);
}



// int main(int argc, char const *argv[])
// {
// 	int i = 0;
// 	char *str = "\"ls\"  \"hassan\"   \"pp\"   \"pp\"   ";
// 	printf("%s\n-------\n", str);
// 	t__lst_token *t = NULL;
// 	ft__lst_tokenize(&t, str);

// 	// printf("t: %s\n", t->str);
// 	t__lst_token *cur = t;
// 	while (cur)
// 	{
// 		printf("%s$\n", cur->str);
// 		cur = cur->next;
// 	}
// 	return 0;
// }

// [ls," ", "-a", "|", "cat"]