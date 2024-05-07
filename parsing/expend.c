/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:12:12 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/04 22:05:05 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = *index + 1;
	len = 1;
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
		{
			
			t__lst_token	*next;
			t__lst_token	*tmp;
			t__lst_token	*parent;
			char **value_twod_array;
			int i = 0;
			char *value;
			
			parent = cur;
			next = cur->next;
			cur->str = ft_get_env_val(lst_env, cur->str + 1);
			if (cur->str && is_with_SPACEs(cur->str[0]))
			{
				tmp = ft_new_token(cur->str, cur->type);
				cur->str = " ";
				cur->type = SPACE;
				cur->next = tmp;
				cur = cur->next;
			}
			if (cur->str != NULL)
			{
				value_twod_array = ft_split_ws(cur->str);
				// printf("------------ %s \t %s \n", value_twod_array[0], value_twod_array[1]);
				// if (value_twod_array == NULL)
				// {
				// 	printf("sad\n");
				// 	cur->str = "";
				// 	cur->next = next;
				// 	continue;
				// }
				cur->str = value_twod_array[i++];
				// printf("var = %s\n", cur->str);
				cur->next = ft_new_token(" ", SPACE);
				cur = cur->next;
				
				while (value_twod_array[0] && value_twod_array[i])
				{
					cur->next = ft_new_token(value_twod_array[i], WORD);
					// printf("-----%s\n", cur->next->str);
					i++;
					if (value_twod_array[i] == 0)
					{
						cur = cur->next;
						continue;
					}
					cur->next->next = ft_new_token(" ", SPACE);
					cur = cur->next->next;
				}
				printf("-----%s\n", parent->str);
				printf("-----%s\n", parent->next->next->str);
				// printf("-----%d\n", parent->next->type);
				cur->next = next;
			}
		}
		else if(cur->type == DOUB_Q)
		{
			char *res = cur->str;
			int i = 0;
			while (i < ft_strlen(res))
			{
				if (res[i] == '$' && res[i + 1] != 0 && (ft_isalnum(res[i + 1]) || res[i + 1] == '_'))
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
			tmp = "";
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
