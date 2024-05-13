/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:34:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/13 18:19:21 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int ft_heredoc(t__lst_token **lst_token)
// {
// 	t__lst_token	*token;
// 	char			*limiter;
// 	char			*buffer;
// 	char			*file_name;
// 	int				fd = 1;
// 	int				n;

// 	while (1)
// 	{
// 		token = ft_get_token_by_type(lst_token, HEARDOC);
// 		if (token == NULL)
// 			break;
// 		limiter = token->next->str;
// 		if (token->next->type == WSP && token->next->next)
// 			limiter = token->next->next->str;
// 		fd = -1;
// 		n = 0;
// 		while (fd == -1)
// 		{
// 			file_name = ft_strjoin(ft_strjoin(".heredoc", ft_itoa(n++)), ".txt");
// 			fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 777);
// 		}
// 		printf("fd: %d\n", fd);
// 		if (fd >= 0)
// 		{
// 			char *input;
// 			input = "";
// 			printf("limiter %s\n", limiter);
// 			while(1)
// 			{
// 				input = readline(">");
// 				if (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0)
// 					break;
// 				write(fd, input, ft_strlen(input));
// 				write(fd, "\n", 1);
// 				free(input);
// 			}
// 			close(fd);
// 			unlink(file_name);	
// 			// token->str = file_name;
// 			// token->type = INPUT;
// 			token = token->next;
// 			// if (token->next)
// 			// 	token->next->next->type = WSP;
// 			if (token->next && token->next->type == WSP && token->next->next)
// 				token->next = token->next->next->next;
// 			printf("str :%s\n", token->str);
// 		}
// 		else
// 			break;
// 	}
// 	return 1;
// }

t__lst_token *ft_next_token(t__lst_token **token)
{
	t__lst_token *cur;

	cur = (*token)->next;
	while (cur && cur->type == WSP)
		cur = cur->next;
	return cur;
}

char	*ft_expend_input(char *input, t_lst_env **lst_env)
{
	int		i;
	char	*new_input;
	int		start;

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
		else if (input[i] == '$' && (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
		{
			start = ++i;
			char *var = ft_handle_var(lst_env, input + i, &i);
			if (var == NULL)
				var = "";
			// printf("var: %s\n", var);
			new_input = ft_strjoin(new_input ,var, ALLOC);
		}
		else
		{
			start = i;
			while (input[i] && input[i] != '$')
				i++;
			new_input = ft_strjoin(new_input ,ft_substr(input, start, i - start, ALLOC), ALLOC);
		}
	}
	return (new_input);
}

int ft_heredoc(t__lst_token **lst_token, t_lst_env **lst_env)
{
	t__lst_token	*token;
	t__lst_token	*next_token;
	char			*limiter;
	char			*buffer;
	char			*file_name;
	
	int				fd = 1;
	int				n;
	int				acs;

	acs = 0;
	
	while (acs == 0)
	{
		void *v = gc_alloc(0, ALLOC);
		file_name = ft_strjoin(ft_strjoin("/tmp/.", ft_itoa((int)&v + n++, ALLOC), ALLOC), ".txt", ALLOC);
		acs = access(file_name, F_OK);
	}
	while (1)
	{
		token = ft_get_token_by_type(lst_token, HEARDOC);
		if (token == NULL)
			break;
		next_token = token->next;
		if (next_token && next_token->type == WSP)
			next_token = next_token->next;
		if (next_token == NULL)
			break;
		limiter = token->next->str;
		if (token->next->type == WSP && token->next->next)
			limiter = token->next->next->str;
		fd = -1;
		buffer = "";
		char *input;
		n = 0;
		while(1)
		{
			input = readline("> ");
			if (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0)
				break;
			if (ft_next_token(&token)->type == WORD)
				input = ft_expend_input(input, lst_env);
			buffer = ft_strjoin(ft_strjoin(buffer, input, ALLOC), "\n", ALLOC);
			// if (input)
			// 	free(input);
			// if (input && input[0] != 0)
			// 	free(input);
		}
		// printf("================\n");
		token->str = file_name;
		token->type = WORD;
		token->next = token->next->next;
		if (token->next && (token->next->type == WORD || token->next->type == SING_Q || token->next->type == DOUB_Q))
			token->next = token->next->next;
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		if (ft_get_token_by_type(lst_token, HEARDOC) == NULL)
			write(fd, buffer, ft_strlen(buffer));
		close(fd);
	}
	return 1;
}
