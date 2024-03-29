#include "minishell.h"

t_token *ft_new_token(char *str, t_type type)
{
    t_token* token;

	if (str == NULL)
		return NULL;
    token = malloc(sizeof(t_token));
    token->str = str;
    token->type = type;
    token->next = NULL;
    return (token);
}

t_token	*ft_token_last(t_token *lst)
{
	t_token	*cur;

	cur = lst;
	if (!lst)
		return (NULL);
	while (cur->next)
		cur = cur->next;
	return (cur);
}

void    ft_token_add_back(t_token **lst, t_token *token)
{
	if (lst == NULL || token == NULL)
		return ;
	if (*lst == NULL)
		*lst = token;
	else
		ft_token_last(*lst)->next = token;
}

void print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("%s\t", lst->str);
		if (lst->type == WORD)
			printf("WORD\n");
		else if (lst->type == SPACE)
			printf("SPACE\n");
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
		else if (lst->type == SING_Q)
			printf("SING_Q\n");
		else if (lst->type == DOUB_Q)
			printf("DOUB_Q\n");

		lst = lst->next;
	}
}
