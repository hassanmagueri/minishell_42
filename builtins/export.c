#include "../minishell.h"




char	*ft_join_value_lst(char *s1, char *s2, t_gc_type type)
{
	char	*res;
	int		i;
	size_t	size;
	int		lens1;

	if (!s1 && !s2)
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	size = ft_strlen((char *)s2) + lens1 + 1;
	// res = malloc(size);
	res = gc_alloc(size, type);
	if (!res)
		return (NULL);
	i = 0;
	while (s2[i - lens1])
	{
		res[i] = s2[i - lens1];
		i++;
	}
	res[i] = 0;
	return (res);
}

void print_lst_export(t_lst_env *lst)
{
	t_lst_env *cur;
	cur = lst;
	while (cur)
	{
		printf("declare -x ");
		if (cur->value)
		{
			printf("%s", cur->key);
			printf("=\"%s\"\n", cur->value);
		}
		else
			printf("%s\n", cur->key);
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

	if (*lst == NULL)
		ft_lst_add_back_env(lst, ft_new_env("OLDPWD", NULL));
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
	print_lst_export(cur);
}

int	index_key(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '+' && str[i + 1] == c) || str[i] == c)
			return i;
		i++;
	}
	return -1;
}
int ft_check_lst_key(t_lst_env **lst,char *key)
{
	t_lst_env	*cur;

	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->key,key,ft_strlen(key)) == 0)
			return(1);
		cur = cur->next;
	}
	return (0);
}
void	ft_change_val(t_lst_env **lst ,char *key,char *value)
{
	t_lst_env	*cur;
	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->key,key,ft_strlen(key)) == 0)
		{
			if (value != NULL)
				cur->value = value;
			break;
		}
		cur = cur->next;
	}
}
void	ft_add_val(t_lst_env	**lst,char *key ,char *val)
{
	t_lst_env	*cur;
	cur = *lst;
	while (cur)
	{
		if (ft_strncmp(cur->key,key,ft_strlen(key)) == 0)
		{
			if (cur->value == NULL)
				cur->value = ft_join_value_lst(cur->value, val, ALLOC_ENV);
			else
				cur->value = ft_strjoin(cur->value,val,ALLOC_ENV);
			break;
		}
		cur = cur->next;
	}
}
int	ft_prasing_export(char *str)
{
	int i;

	i = 0;
	if (ft_isdigit(str[0])==1 || str[0]=='\0' || str[0] == '=')
		return (1);
	while(str[i]=='_')
		i++;
	while(str[i])
    {
		if (str[i]=='_')
			i++;
		// else if (str[i]=='$' && str[i + 1]=='?')
		// 	return (i);
		else if (ft_isalnum(str[i])!=1)
			return (1);
        else
			i++;
    }
	return (0);
}
int	ft_export(t_lst_env **lst_env, t_cmd *str)
{
	int		len;
	int		status;
	status = 0;
	char	*value;
	char	*key;
	int i;
	i = 1;
	// if (*lst_env== NULL)
	// 	return 1;
	if (str->cmd[i]== NULL)
		print_lst_order_alpha(lst_env);
	else
	{
		while (str->cmd[i])
		{
			if (str->cmd[i]==NULL)
			{
				i++;
				continue;
			}
			len = index_key(str->cmd[i], '=');
			if (len != -1)
			{
				key = ft_substr(str->cmd[i], 0, len, ALLOC_ENV);
				value = ft_strchr(str->cmd[i], '=') + 1;
			}
			else
			{
				key = ft_strdup(str->cmd[i], ALLOC_ENV);
				value = ft_strdup(NULL, ALLOC_ENV);;
			}
			if (ft_prasing_export(key) == 1)
			{
				// printf("export: `%s': not a valid identifier\n",str->cmd[i]);
				ft_putstr_fd("export: `",2);
				ft_putstr_fd(str->cmd[i],2);
				ft_putendl_fd("': not a valid identifier",2);
				status = 1;
				i++;
				continue;
			}
			if (ft_check_lst_key(lst_env,key) == 1)
			{
				if (len != -1 && str->cmd[i][len] == '+')
					ft_add_val(lst_env,key,value);
				else
					ft_change_val(lst_env,key,value);
			}
			else
				 ft_lst_add_back_env(lst_env, ft_new_env(key, value));
			i++;
		}
	}
	return (status);
}
