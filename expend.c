/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/04/17 11:48:38 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_handle_var(t_lst_env **lst_env, char *old_output, int *index)
{
	// int i;
	int len;
	char *s;

	len = 0;
	if (ft_isdigit(old_output[len]))
		len++;
	else
		while (old_output[len] &&
				(ft_isalnum(old_output[len]) || old_output[len] == '_'))
			len++;
	s = ft_get_env_val(lst_env, ft_strnjoin("", old_output, len));
	(*index) += len;
	return (s);
}

char *ft_handle_simple_string(char *old_output, char *new_output,int *index)
{
	int		len;
	int		i;
	// char	*tmp;

	i = *index + 1;
	len = 1;
	// i++;
	while (old_output[len] && old_output[len] != '$')
		len++;
	new_output = ft_strnjoin(new_output, old_output, len);
	(*index) += len;
	return new_output;
}

int ft_expand(t__lst_token **lst_token, t_lst_env **lst_env)
{
	t__lst_token	*cur;
	char			*tmp;
	char			*var;

	cur = *lst_token;
	tmp = "";
	while (cur)
	{
		if (cur->type == VAR)
			cur->str = ft_get_env_val(lst_env, cur->str + 1);
		else if(cur->type == DOUB_Q)
		{
			char *res = cur->str;
			int i = 0;
			while (i < ft_strlen(res))
			{
				if (res[i] == '$' && (ft_isalnum(res[i + 1]) || res[i + i] == '_'))
				{
					i++;
					var = ft_handle_var(lst_env, res + i, &i);
					tmp = ft_strjoin(tmp, var);
				}
				else if(res[i] == '$' && res[i + 1] == '$')
				{
					i += 2;
					tmp = ft_strjoin(tmp, "$$");
				}
				else
					tmp = ft_handle_simple_string(res + i, tmp, &i);
			}
			cur->str = tmp;
		}
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
