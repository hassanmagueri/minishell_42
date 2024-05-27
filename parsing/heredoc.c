/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:34:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/27 16:56:06 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t__lst_token *ft_next_token(t__lst_token **token)
{
	t__lst_token *cur;

	cur = (*token)->next;
	while (cur && cur->type == WSP)
		cur = cur->next;
	return cur;
}

char *ft_expend_input(char *input, t_lst_env **lst_env)
{
	int i;
	char *new_input;
	int start;

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
			new_input = ft_strjoin(new_input, var, ALLOC);
		}
		else
		{
			start = i;
			while (input[i] && input[i] != '$')
				i++;
			new_input = ft_strjoin(new_input, ft_substr(input, start, i - start, ALLOC), ALLOC);
		}
	}
	return (new_input);
}

int ft_heredoc(t__lst_token **lst_token, t_lst_env **lst_env)
{
	t__lst_token *token;
	t__lst_token *next_token;
	char *limiter;
	char *buffer;
	char *file_name;
	int fd_heredoc;
	int fd = 1;
	int n;
	int acs;
	char *input;

	acs = 0;

	while (acs == 0)
	{
		void *v = gc_alloc(0, ALLOC);
		file_name = ft_strjoin(ft_strjoin("/tmp/.", ft_itoa((int)&v + n++, ALLOC), ALLOC), ".txt", ALLOC);
		acs = access(file_name, F_OK);
	}
	token = *lst_token;
	while (1)
	{
		token = ft_get_token_by_type(&token, HEARDOC);
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
		n = 0;
		int sec_fd_in;
		sec_fd_in = dup(0);
		while (1)
		{
			signal(SIGINT, handle_heredoc);
			input = readline("> ");
			if (input == NULL)
				break;
			char *tmp_input = input;
			if (ft_strncmp(tmp_input, limiter, ft_strlen(limiter) + 1) == 0)
			{
				free(input);
				break;
			}
			if (ft_next_token(&token)->type == WORD)
				tmp_input = ft_expend_input(tmp_input, lst_env);
			buffer = ft_strjoin(ft_strjoin(buffer, tmp_input, ALLOC), "\n", ALLOC); // ! free tmp_input of read line
			if (input)
				free(input);
		}
		dup2(sec_fd_in, 0);
		close(sec_fd_in);
		token = token->next;
		if (token->next && (token->next->type == WORD || token->next->type == SING_Q || token->next->type == DOUB_Q))
			token = token->next;
		fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		fd_heredoc = open(file_name, O_RDWR, 0777);
		token->str = ft_itoa(fd_heredoc, ALLOC);
		write(fd, buffer, ft_strlen(buffer));
		close(fd);
		unlink(file_name);
		// exit(1);
	}
	return 1;
}
