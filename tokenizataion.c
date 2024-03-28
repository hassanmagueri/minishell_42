#include "minishell.h"

int is_sep(int c)
{
	return (c == ' ' || c == '|' || c == '\t' ||
			c == '\n' || c == '\"' || c == '\'' ||
			c == '|');
}

int	find_sec(char *s, char c)
{
	int	i;

	if (!s[0])
		return -1;
	i = 1;
	while (s[i])
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return -1;
}

void    ft_tokenize(t_token **token, char *cmd)
{
	int		i;
	int		index;
	char	c;

	index = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			ft_token_add_back(token, ft_new_token(ft_substr(cmd, i++, 1), PIPE));
		else if (cmd[i] == '\"')
		{
			int	len = find_sec(cmd + i, '\"');
			char *str = ft_substr(cmd, i, len + 1);
			t_token *t = ft_new_token(str, DOUB_Q);//"echo"
			ft_token_add_back(token, t); // "echo" -a
			printf("len: %d\n", len + 1);
			printf("i: %d\n", i);
			printf("str: %s\n--------\n", str);
			i += len + 1;
		}
		else 
			i++;
	}
}

int main(int argc, char const *argv[])
{
	int i = 0;

	char *str = "\"ls\"        \"hassan\"   \"pp\"   \"pp\"   ";
	printf("%s\n-------\n", str);
	t_token *t = NULL;
	ft_tokenize(&t, str);

	// printf("t: %s\n", t->str);
	t_token *cur = t;
	while (cur)
	{
		printf("%s$\n", cur->str);
		cur = cur->next;
	}
	return 0;
}
// [ls," ", "-a", "|", "cat"]