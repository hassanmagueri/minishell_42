/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizataion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:34 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/20 11:23:12 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_with_spaces(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int is_sep(int c)
{
	return
	(
		ft_is_with_spaces(c) || c == '|' || c == '\"'
			|| c == '\'' || c == '<' || c == '>' || c == '|' || c == '$'
	);
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
	if (input == NULL)
		return (0);
	while (input[i])
	{
		if (input[i] == '|')
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i++, 1, ALLOC), PIPE));
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i++, 2, ALLOC), HEARDOC));
			else
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 1, ALLOC), INPUT));
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i++, 2, ALLOC), APPEND));
			else
				ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 1, ALLOC), OUTPUT));
			i++;
		}
		else if (input[i] == '\"')
		{
			int len = find_sec(input + i, '\"') + 1;
			if (len == 0)
				len++;
				// return (print_error(NULL));
			char *str = ft_substr(input, i, len, ALLOC);
			printf("str: %s\n", str);
			t__lst_token *t = ft_new_token(str, DOUB_Q);
			// t__lst_token *t = ft_new_token(ft_strtrim(str, "\"", ALLOC), DOUB_Q);
			ft_lst_token_add_back(token, t);
			i += len;
		}
		else if (input[i] == '\'')
		{
			int len = find_sec(input + i, '\'') + 1;
			if (len == 0)
				len++;
			// return (print_error(NULL));
			char *str = ft_substr(input, i, len, ALLOC);
			printf("str: %s\n", str);
			t__lst_token *t = ft_new_token(str, SING_Q);
			// t__lst_token *t = ft_new_token(ft_strtrim(str, "\'", ALLOC), SING_Q);
			ft_lst_token_add_back(token, t);
			i += len;
		}
		else if (ft_is_with_spaces(input[i]))
		{
			while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
				i++;
			ft_lst_token_add_back(token, ft_new_token(" ", WSP));
		}
		else if (input[i] == '$' && input[i + 1] == '$')
		{
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 2, ALLOC), WORD));
			i += 2;
		}
		else if (input[i] == '$' && input[i + 1] == '?')
		{
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, i, 2, ALLOC), EXIT_STATUS));
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
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, start, i - start, ALLOC), VAR));
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
			// printf("%d\n", input[i]);
			ft_lst_token_add_back(token, ft_new_token(ft_substr(input, start, i - start, ALLOC), WORD));
		}
		// printf("%s", ft__lst_token_last(*token)->str);
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