#include "../minishell.h"

// data---> data->new_env= env
//new_env[last]
typedef struct s_data
{
	char	**new_env;
}	t_data;
void	handl_error_syntax(char **args)
{
	int	i;

	i = 1;
	while(args[i])
	{
		
		i++;
	}
}
int	ft_argslen(char **str)
{
	int n;
	n = 0;
	while(*str)
	{
		str++;
		n++;
	}
	return (n);
}
char	**ft_export(char **env ,char *str)
{
	char **args_exp;
	int i = 0;
	int j = 1;
	char **new_e;
	int number_args;
	int number_args1;
	args_exp = ft_split(str, ' ');
	handl_error_syntax(args_exp);
	number_args = ft_argslen(args_exp) - 1;
	number_args1 = ft_argslen(env);
	new_e = (char **)malloc(sizeof(char *) * (number_args1 + number_args + 1));
	if (!new_e)
		return (NULL);
	while(i < number_args1 - 1)
	{
		new_e[i] = ft_strdup(env[i]);
		i++;
	}
	while(j <= number_args)
	{
		new_e[i] = ft_strdup(args_exp[j]);
		i++;
		j++;
	}
	new_e[i++] = ft_strdup(env[number_args1- 1]);
	new_e[i] = NULL;
	return (new_e);
}

int main(int ac,char *av[],char *env[])
{
	int n;
	int	i;
	char **str;
	i = 0;

	// str = ft_dup_env(env);
	str = ft_export(env ,av[1]);
	// printf("envlen = %d\n",n);
	while(str[i])
		printf("%s\n",str[i++]);
}