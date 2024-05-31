/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 22:43:35 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/31 16:42:11 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lst_token	*ft_get_next_token(t_lst_token *node)
{
	t_lst_token	*cur;

	cur = node;
	while (cur)
	{
		if (cur->type == WSP)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_lst_token	*ft_new_token(char *str, t_type type)
{
	t_lst_token	*token;

	if (str == NULL)
		return (NULL);
	token = gc_alloc(sizeof(t_lst_token), ALLOC);
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_lst_token	*ft_lst_token_last(t_lst_token **lst)
{
	t_lst_token	*cur;

	cur = *lst;
	if (!lst)
		return (NULL);
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void	ft_lst_token_add_back(t_lst_token **lst, t_lst_token *token)
{
	if (lst == NULL || token == NULL)
		return ;
	if (*lst == NULL)
		*lst = token;
	else
		ft_lst_token_last(lst)->next = token;
}

void	print_lst_tokens(t_lst_token *lst)
{
	while (lst)
	{
		printf("(%s)\t", lst->str);
		if (lst->type == WORD)
			printf("WORD\n");
		else if (lst->type == WSP)
			printf("WSP\n");
		else if (lst->type == APPEND)
			printf("APPEND\n");
		else if (lst->type == HEARDOC)
			printf("HEARDOC\n");
		else if (lst->type == INPUT)
			printf("INPUT\n");
		else if (lst->type == OUTPUT)
			printf("OUTPUT\n");
		else if (lst->type == VAR)
			printf("VAR\n");
		else if (lst->type == PIPE)
			printf("PIPE\n");
		else if (lst->type == DOUB_Q || lst->type == SING_Q)
			printf("DOUB_Q\n");
		else if (lst->type == EXIT_STATUS)
			printf("EXIT_STATUS\n");
		lst = lst->next;
	}
}
