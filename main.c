#include "minishell.h"

int main(int argc, char *argv[], char **env) {
	char *cmd;
	t_lst_env *lst_env;

	lst_env = NULL;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	while (1)
	{
		t__lst_token *t = NULL;
		// cmd = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		cmd = readline("minishell -> ");
		ft__lst_tokenize(&t, cmd);
		ft_expand(&t, &lst_env);
		// add_history(cmd);
		print__lst_tokens(t);
		free(cmd);
		
		// if (ft_strncmp(cmd, "ls ", 3) == 0)
		//     execve("/") 
	}
	return 0;
}