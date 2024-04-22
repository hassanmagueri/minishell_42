#include "../minishell.h"

t_lst_env	*ft_lst_env_last(t_lst_env *lst)
{
	t_lst_env	*cur;

	cur = lst;
	if (!lst)
		return (NULL);
	while (cur->next)
		cur = cur->next;
	return (cur);
}

t_lst_env *ft_new_env(char *key,char *value)
{
	t_lst_env	*node;

	node = malloc(sizeof(t_lst_env));
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return node;
}

int ft_lst_add_back_env(t_lst_env **lst_env, t_lst_env *node_env)
{
    if (lst_env == NULL)
		return (-1);
	if (*lst_env == NULL)
		*lst_env = node_env;
	else
		ft_lst_env_last(*lst_env)->next = node_env;
	return (0);
}
int	index_of(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return i;
		i++;
	}
	return -1;
}

int	init_env(t_lst_env **lst, char **env)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		len = index_of(env[i], '=');
		if (len == -1)
			i++;
		value = ft_strchr(env[i], '=') + 1;
		ft_lst_add_back_env(lst, ft_new_env(ft_substr(env[i], 0, len), value));
		i++;
	}
	return 1;
}

void print_lst_env(t_lst_env *lst)
{
	t_lst_env *cur;
	cur = lst;
	while (cur)
	{
		printf("declare -x ");
		printf("%s", cur->key);
		printf("=\"%s\"\n", cur->value);
		cur = cur->next;
	}
}

int	ft_strcmp(char *s1,char *s2)
{
	int i;
	i = 0;

	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}
void	print_lst_order_alpha(t_lst_env **lst)
{
	t_lst_env	*cur;
	// printf("\n\n\n\n\n");
	// print_lst_env(*lst);
	cur = *lst;
	while(cur->next!= NULL)
	{
		if (ft_strcmp(cur->key,cur->next->key) > 0)
		{
		  	char *temp = cur->key;
		  	char *temp1 = cur->value;
            cur->key = cur->next->key;
			cur->value = cur->next->value;
            cur->next->key = temp;
            cur->next->value = temp1;
			cur= *lst;
		}
		else
			cur = cur->next;
	}
	cur = *lst;
	print_lst_env(cur);
}


int	ft_export(t_lst_env *lst_env, t_cmd *str)
{
	int		len;
	char	*value;
	int i;
	i = 1;

	if (str->cmd[i]== NULL)
	{
		print_lst_order_alpha(&lst_env);
	}
	else
	{
		while (str->cmd[i])
		{
			len = index_of(str->cmd[i], '=');
			if (len == -1)
				return -1;
			value = ft_strchr(str->cmd[i], '=') + 1;
			ft_lst_add_back_env(&lst_env, ft_new_env(ft_substr(str->cmd[i], 0, len), value));
			i++;
		}
	}

	return (1);
}

// int main(int ac,char *av[],char *env[])
// {
// 	char *str;
// 	t_lst_env *lst_env;
// 	// t_lst_env **lst_env1;
// 	init_env(&lst_env,env);
// 	// str = "export sd=1233 de=12122 ueueue=353553 uerh=6671266262";
// 	// ft_export(lst_env,str);
// 	print_lst_order_alpha(&lst_env);
// 	// print_lst_env(*lst_env1);
// }

// // first step init_env 
// // if (str == env)--> print_env
// // if (str == export)--> add arg_env to env
