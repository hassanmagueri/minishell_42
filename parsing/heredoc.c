/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 22:34:15 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/29 15:04:42 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_heredoc(t__lst_token **lst_token)
{
	t__lst_token	*token;
	char			*limiter;
	char			*buffer;
	char			*file_name;
	int				fd = 1;
	int				n;

	while (1)
	{
		token = ft_get_token_by_type(lst_token, HEARDOC);
		if (token == NULL)
			break;
		limiter = token->next->str;
		if (token->next->type == SPACE && token->next->next)
			limiter = token->next->next->str;
		fd = -1;
		n = 0;
		while (fd == -1)
		{
			file_name = ft_strjoin(ft_strjoin(".heredoc", ft_itoa(n++)), ".txt");
			fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 777);
		}
		printf("fd: %d\n", fd);
		if (fd >= 0)
		{
			char *input;
			input = "";
			printf("limiter %s\n", limiter);
			while(1)
			{
				input = readline(">");
				if (ft_strncmp(input, limiter, ft_strlen(limiter) + 1) == 0)
					break;
				write(fd, input, ft_strlen(input));
				write(fd, "\n", 1);
				free(input);
			}
			close(fd);
			unlink(file_name);	
			// token->str = file_name;
			// token->type = INPUT;
			token = token->next;
			// if (token->next)
			// 	token->next->next->type = SPACE;
			if (token->next && token->next->type == SPACE && token->next->next)
				token->next = token->next->next->next;
			printf("str :%s\n", token->str);
		}
		else
			break;
	}
	return 1;
}
//<< -> f1 -> NULL


