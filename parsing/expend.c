/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/26 19:19:18 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_handle_var(t_lst_env **lst_env, char *key, int *index)
{
	// int i;
	int len;
	char *s;

	len = 0;
	if (ft_isdigit(key[len]))
		len++;
	else
		while (key[len] && (ft_isalnum(key[len]) || key[len] == '_'))
			len++;
	s = ft_get_env_val(lst_env, ft_strnjoin("", key, len, ALLOC));
	if (!s)
		s = "";
	if (index != NULL)
		(*index) += len;
	return (s);
}

char *ft_handle_simple_string(char *old_output, char *new_output, int *index)
{
	int len;
	int i;

	i = *index + 1;
	len = 1;
	while (old_output[len] && old_output[len] != '$')
		len++;
	new_output = ft_strnjoin(new_output, old_output, len, ALLOC);
	(*index) += len;
	return new_output;
}

char *ft_first_cmd(t__lst_token **lst_token)
{
	t__lst_token *cur;
	char *res;

	res = "";
	cur = *lst_token;
	while (cur && cur->type != WORD && cur->type != DOUB_Q && cur->type != SING_Q)
		cur = cur->next;
	while (cur && (cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q))
	{
		res = ft_strjoin(res, cur->str, ALLOC);
		cur = cur->next;
	}
	return (res);
}

int ft_is_endl_with_with_space(char *str)
{
	int len;

	len = ft_strlen(str);
	if (ft_is_with_spaces(str[len - 1]))
		return 1;
	return 0;
}

int ft_is_strong_word_befor(t__lst_token **lst_token, t__lst_token *last)
{
	t__lst_token *cur;

	cur = *lst_token;
	while (cur && cur->type != WORD && cur->type != DOUB_Q && cur->type != SING_Q)
		cur = cur->next;
	while (cur && (cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q))
		cur = cur->next;
	// skip first cmd to approach the args
	if (cur->type == VAR)
		return (1);
	while (cur != last)
	{
		// if ((cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q) && cur->str[0] != '\0')
		if (((cur->type == WORD || cur->type == DOUB_Q || cur->type == SING_Q) && cur->str[0] != '\0'))
			return (1);
		cur = cur->next;
	}
	return (0);
}

int ft_expand(t__lst_token **lst_token, t_lst_env **lst_env, int *exit_state)
{
	t__lst_token *cur;
	t__lst_token *prev;
	char *tmp;
	char *var;
	char *first_cmd = ft_first_cmd(lst_token);
	prev = NULL;
	cur = *lst_token;
	tmp = "";
	while (cur)
	{
		if (cur->type == EXIT_STATUS)
			cur->str = ft_itoa(*exit_state, ALLOC);
		else if (cur->type == VAR)
		{

			t__lst_token *next;
			t__lst_token *tmp;
			t__lst_token *parent;
			char **value_twod_array;
			int i = 0;
			char *value;

			parent = cur;
			next = cur->next;
			cur->str = ft_get_env_val(lst_env, cur->str + 1);
			if (ft_strncmp(first_cmd, "export", ft_strlen(first_cmd) + 1) == 0)
			// return (1);
			{
				cur = next;
				continue;
			}
			// if (cur->str == NULL)
			// {
			// 	if (prev)
			// 		prev->next = cur->next;
			// 	cur = cur->next;
			// 	continue;
			// }
			// if (cur->str && ft_is_with_spaces(cur->str[0]) && prev && (prev->type == VAR || (ft_is_strong_word_befor(lst_token, cur->next)))) // add also DOUB_Q and SING_Q
			if (cur->str && ft_is_with_spaces(cur->str[0]) && prev && (prev->type == VAR || (ft_is_strong_word_befor(lst_token, cur->next)))) // add also DOUB_Q and SING_Q
			{
				tmp = ft_new_token(cur->str, cur->type);
				cur->str = " ";
				cur->type = WSP;
				cur->next = tmp;
				cur = cur->next;
			}
			char *str;
			if (cur->str != NULL)
			{
				str = cur->str;
				value_twod_array = ft_split_ws(cur->str, ALLOC);
				cur->str = value_twod_array[i++];
				if (value_twod_array[i] != 0)
				{
					cur->next = ft_new_token(" ", WSP);
					cur = cur->next;
				}
				while (value_twod_array[0] && value_twod_array[i])
				{
					cur->next = ft_new_token(value_twod_array[i], WORD);
					i++;
					if (value_twod_array[i] == 0)
					{
						cur = cur->next;
						continue;
					}
					cur->next->next = ft_new_token(" ", WSP);
					cur = cur->next->next;
				}
				// if (next && next->type != VAR && next->type != WSP)
				// if (next && (next->type != VAR || ft_is_endl_with_with_space(str)) && next->type != WSP)
				if (next && (ft_is_endl_with_with_space(str)) && next->type != WSP)
				{
					cur->next = ft_new_token(" ", WSP);
					cur = cur->next;
				}
				cur->next = next;
			}
		}
		else if (cur->type == DOUB_Q)
		{
			char *res = cur->str;
			int i = 0;
			while (i < ft_strlen(res))
			{
				if (res[i] == '$' && res[i + 1] == '$')
				{
					i += 2;
					tmp = ft_strjoin(tmp, "$$", ALLOC);
				}
				if (res[i] == '$' && res[i + 1] == '?')
				{
					i += 2;
					tmp = ft_strjoin(tmp, ft_itoa(*exit_state, ALLOC), ALLOC);
				}
				else if (res[i] == '$' && res[i + 1] != 0 && (ft_isalnum(res[i + 1]) || res[i + 1] == '_'))
				{
					i++;
					var = ft_handle_var(lst_env, res + i, &i);
					tmp = ft_strjoin(tmp, var, ALLOC);
				}
				else
					tmp = ft_handle_simple_string(res + i, tmp, &i);
			}
			cur->str = tmp;
			tmp = "";
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}

// int main(int argc, char const *argv[], char **env)
// {
// 	char *s = ft_strdup("$USER");
// 	char *tmp;
// 	char *out = "";
// 	t_lst_env *lst_env;
// 	init_env(&lst_env, env);
// 	int i = 0;
// 	// printf("%s\n", out);
// 	// out = ft_handle_var(&lst_env, s, out, &i);
// 	// i = 16;
// 	// out = ft_handle_simple_string(s + i, out, &i);
// 	printf("%s\n", out);
// 	return 0;
// }
