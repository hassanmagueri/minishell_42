/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:34:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/31 16:58:36 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_file_name(void)
{
	int		acs;
	int		n;
	void	*v;
	char	*file_name;

	acs = 0;
	n = 0;
	while (acs == 0)
	{
		v = gc_alloc(0, ALLOC);
		file_name = ft_strjoin(ft_strjoin("/tmp/.",
					ft_itoa((int)&v + n++, ALLOC), ALLOC),
				".txt", ALLOC);
		acs = access(file_name, F_OK);
	}
	return (file_name);
}

char	*ft_get_delimiter(t_lst_token *token)
{
	t_lst_token		*next_token;
	char			*delimiter;

	next_token = token->next;
	if (next_token && next_token->type == WSP)
		next_token = next_token->next;
	if (next_token == NULL)
		return (NULL);
	delimiter = token->next->str;
	if (token->next->type == WSP && token->next->next)
		delimiter = token->next->next->str;
	return (delimiter);
}

char	*ft_buffering_heredoc(t_lst_token **token, t_lst_env **lst_env,
			char *delimiter, int exit_status)
{
	char	*buffer;
	char	*input;
	char	*tmp_input;

	buffer = "";
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			return (buffer);
		tmp_input = input;
		if (ft_strncmp(tmp_input, delimiter, ft_strlen(delimiter) + 1) == 0)
			return (free(input), buffer);
		if (ft_next_token(token)->type == WORD
			|| ft_next_token(token)->type == VAR
			|| ft_next_token(token)->type == EXIT_STATUS)
			tmp_input = ft_expend_input(tmp_input, lst_env, exit_status);
		buffer = ft_strjoin(
				ft_strjoin(buffer, tmp_input, ALLOC), "\n", ALLOC);
		free(input);
	}
	return (buffer);
}

int	ft_heredoc_loop(t_lst_token *token, t_lst_env **lst_env, int exit_status)
{
	int		fd;
	char	*buffer;
	char	*delimiter;
	char	*file_name;

	while (1)
	{
		token = ft_get_token_by_type(&token, HEARDOC);
		if (token == NULL)
			break ;
		file_name = ft_file_name();
		delimiter = ft_get_delimiter(token);
		buffer = ft_buffering_heredoc(&token, lst_env, delimiter, exit_status);
		if (isatty(0) == 0)
			return (token->type = WORD, token->next = NULL, 1);
		fd = open(file_name, O_CREAT | O_WRONLY, 0600);
		write(fd, buffer, ft_strlen(buffer));
		close(fd);
		fd = open(file_name, O_RDWR, 0777);
		token = ft_next_token(&token);
		token->str = ft_itoa(fd, ALLOC);
		unlink(file_name);
	}
	return (0);
}

int	ft_heredoc(t_lst_token **lst_token, t_lst_env **lst_env, int exit_status)
{
	t_lst_token		*token;
	t_lst_token		*cur;
	int				sec_fd_in;

	token = *lst_token;
	sec_fd_in = dup(0);
	signal(SIGINT, handle_heredoc);
	if (ft_heredoc_loop(token, lst_env, exit_status))
	{
		cur = *lst_token;
		while (cur)
		{
			if (cur->type == HEARDOC)
				close(ft_atoi(ft_next_token(&cur)->str));
			cur = cur->next;
		}
		*lst_token = NULL;
	}
	dup2(sec_fd_in, 0);
	close(sec_fd_in);
	return (1);
}
