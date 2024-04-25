#include "minishell.h"

void	init_path_env(t_data *pip,char *env[])
{
	char **str;
	while (env && *env && ft_strncmp(*env, "PATH=", 5) != 0)
        env++;
	if (*env == NULL)
		printf("Path not found");
	*env += 5;
	pip->env_path = ft_split (*env, ':');
	if (!pip->env_path)
		printf("Invalid argument");
}


int main(int argc, char *argv[], char **env)
{
	char *input;
	t_lst_env *lst_env;
	t_data	pip;
	char **env_path;
	lst_env = NULL;

	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	init_path_env(&pip, env);

	while (1)
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		if (input == NULL)
			return (1);
		add_history(input);
		// input = readline("minishell -> ");
		// ft__lst_tokenize(&t, input);
		// ft_heredoc(&lst_env);
		if (ft__lst_tokenize(&t, input) || generate_errors(&t) == 1)
			continue;
		ft_expand(&t, &lst_env);
		ft_join(&t);
		ft_cmd(&cmd, &t);
		ft_lst_cmd(lst_env,cmd,&pip);
	}

	return 0;
}