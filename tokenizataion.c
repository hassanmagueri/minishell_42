#include "minishell.h"

int is_sep(int c)
{
	return (c == ' ' || c == '|' || c == '\t' || c == '\"' || c == '\'' || c == '<' || c == '>' || c == '|' || c == '$');
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
}

void ft_tokenize(t_token **token, char *cmd)
{
	int i;
	int index;
	// char	c;

	index = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			ft_token_add_back(token, ft_new_token(ft_substr(cmd, i++, 1), PIPE));
		else if (cmd[i] == '<')
			ft_token_add_back(token, ft_new_token(ft_substr(cmd, i++, 1), INPUT));
		else if (cmd[i] == '>')
			ft_token_add_back(token, ft_new_token(ft_substr(cmd, i++, 1), OUTPUT));
		else if (cmd[i] == '\"')
		{
			int len = find_sec(cmd + i, '\"') + 1;
			if (len == 0)
				return (printf("syntax error\n"), ft_void());
			char *str = ft_substr(cmd, i, len);
			t_token *t = ft_new_token(str, DOUB_Q);
			ft_token_add_back(token, t);
			i += len;
		}
		else if (cmd[i] == ' ')
		{
			while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
				i++;
			ft_token_add_back(token, ft_new_token(" ", SPACE));
		}
		else if (cmd[i] == '$' && ft_isalnum(cmd[i + 1]))
		{
			int start = i;
			i++;
			while (cmd[i] && !is_sep(cmd[i]))
				i++;
			ft_token_add_back(token, ft_new_token(ft_substr(cmd, start, i - start), VAR));
		}
		else //word
		{
			int start = i;
			i++;
			while (cmd[i] && (cmd[i] == '$' || !is_sep(cmd[i])))
			{
				i++;
				if (cmd[i] == '$' && cmd[i -1] == '$')
					break;
			}
			ft_token_add_back(token, ft_new_token(ft_substr(cmd, start, i - start), WORD));
		}
	}
}

// int main(int argc, char const *argv[])
// {
// 	int i = 0;
// 	char *str = "\"ls\"  \"hassan\"   \"pp\"   \"pp\"   ";
// 	printf("%s\n-------\n", str);
// 	t_token *t = NULL;
// 	ft_tokenize(&t, str);

// 	// printf("t: %s\n", t->str);
// 	t_token *cur = t;
// 	while (cur)
// 	{
// 		printf("%s$\n", cur->str);
// 		cur = cur->next;
// 	}
// 	return 0;
// }

// [ls," ", "-a", "|", "cat"]