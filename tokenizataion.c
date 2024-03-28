#include "minishell.h"

int is_sep(int c)
{
	return (c == ' ' || c == '|' || c == '\t' ||
			c == '\n' || c == '\"' || c == '\'' ||
			c == '|');
}

void    ft_tokenize(t_token **token, char *cmd)
{
	int i;
	int index;

	index = 0;
	i = 0;
	while (cmd[i])
	{
		if (is_sep(cmd[i]))
			
		i++;
	}
	
}
