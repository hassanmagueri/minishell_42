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
		return (0);
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
